/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/playable_level.h"

#include <algorithm>
#include <memory>

#include <glm/mat4x4.hpp>

#include <rinvid/core/render_context.h>
#include <rinvid/system/application.h>
#include <rinvid/system/keyboard.h>
#include <rinvid/util/color.h>
#include <rinvid/util/vector2.h>

#include "src/levels/main_menu.h"
#include "src/runtime_ctx.h"

using namespace rinvid;
using namespace rinvid::system;

namespace
{

constexpr const char* FONT_PATH{"resources/ttf/aquifer.ttf"};
constexpr double DEATH_FADE_SECONDS{1.5};
constexpr std::int32_t DEATH_MESSAGE_MAX_WIDTH{760};
constexpr std::int32_t DEATH_MESSAGE_SIDE_PADDING{40};
constexpr std::int32_t DEATH_BUTTON_GAP{54};

const Color DEATH_MESSAGE_COLOR{0xEAF8F5FF};

} // namespace

PlayableLevel::PlayableLevel()
    : death_message_{"This is not how it ends for you",
                     FONT_PATH,
                     {0.0F, 0.0F},
                     DEATH_MESSAGE_COLOR,
                     34,
                     static_cast<float>(DEATH_MESSAGE_MAX_WIDTH),
                     rinvid::gui::LabelAlignment::Center},
      retry_button_{"Retry"}
{
}

void PlayableLevel::create()
{
    death_sequence_active_ = false;
    death_fade_elapsed_ = 0.0;
    death_enter_was_down_ = false;
    death_space_was_down_ = false;
    death_layout_width_ = 0;
    death_layout_height_ = 0;
    death_overlay_ = nullptr;

    create_level();
}

void PlayableLevel::destroy()
{
    destroy_level();
}

void PlayableLevel::destroy_level()
{
}

void PlayableLevel::update(double delta_time)
{
    get_render_context().clear_screen(0.0F, 0.0F, 0.0F, 1.0F);

    PauseAction action{PauseAction::None};
    bool paused{false};

    if (!death_sequence_active_)
    {
        action = pause_menu_.update(delta_time);
        paused = pause_menu_.is_paused();

        if (!paused)
        {
            update_level(delta_time);
            kill_player_if_below_camera();
        }

        if (player_.is_dead())
        {
            start_death_sequence();
        }
    }

    bool should_restart_after_death{false};
    if (death_sequence_active_)
    {
        update_death_sequence(delta_time);
        should_restart_after_death = retry_action_was_pressed();
    }

    draw_level(paused ? 0.0 : delta_time);

    if (paused)
    {
        pause_menu_.draw();
    }

    if (death_sequence_active_)
    {
        draw_death_overlay();
        if (should_restart_after_death)
        {
            get_application()->set_screen(restart_level());
        }
        return;
    }

    handle_pause_action(action);
}

void PlayableLevel::handle_pause_action(PauseAction action)
{
    switch (action)
    {
        case PauseAction::Restart:
            get_application()->set_screen(restart_level());
            break;
        case PauseAction::MainMenu:
            get_application()->set_screen(std::make_unique<MainMenu>());
            break;
        case PauseAction::Quit:
            get_application()->exit();
            break;
        case PauseAction::Resume:
        case PauseAction::None:
        default:
            break;
    }
}

void PlayableLevel::start_death_sequence()
{
    if (death_sequence_active_)
    {
        return;
    }

    death_sequence_active_ = true;
    death_fade_elapsed_ = 0.0;
}

void PlayableLevel::update_death_sequence(double delta_time)
{
    death_fade_elapsed_ = std::min(DEATH_FADE_SECONDS, death_fade_elapsed_ + delta_time);
}

void PlayableLevel::draw_death_overlay()
{
    layout_death_overlay();

    RenderContext* render_context{RenderContext::get_active_context()};
    if (render_context == nullptr)
    {
        return;
    }

    const glm::mat4 old_view{render_context->get_view()};
    render_context->update_view(glm::mat4{1.0F});

    if (death_overlay_ != nullptr)
    {
        death_overlay_->set_color(Color{0.0F, 0.0F, 0.0F, death_fade_alpha()});
        death_overlay_->draw();
    }

    if (death_fade_finished())
    {
        death_message_.draw();
        retry_button_.draw();
    }

    render_context->update_view(old_view);
}

void PlayableLevel::layout_death_overlay()
{
    RenderContext* render_context{RenderContext::get_active_context()};
    if (render_context == nullptr)
    {
        return;
    }

    const std::int32_t screen_width{render_context->get_width()};
    const std::int32_t screen_height{render_context->get_height()};
    if (screen_width == death_layout_width_ && screen_height == death_layout_height_)
    {
        return;
    }

    death_layout_width_ = screen_width;
    death_layout_height_ = screen_height;

    death_overlay_ = std::make_unique<RectangleShape>(
        Vector2f{static_cast<float>(screen_width) / 2.0F, static_cast<float>(screen_height) / 2.0F},
        static_cast<float>(screen_width), static_cast<float>(screen_height));

    const std::int32_t message_width{std::min(
        DEATH_MESSAGE_MAX_WIDTH, std::max(0, screen_width - DEATH_MESSAGE_SIDE_PADDING * 2))};
    const float message_x{(static_cast<float>(screen_width) - static_cast<float>(message_width)) /
                          2.0F};
    const float message_y{static_cast<float>(screen_height) / 2.0F};

    death_message_.set_bounds_width(static_cast<float>(message_width));
    death_message_.set_position({message_x, message_y});

    const std::int32_t button_width{std::min(
        MenuButton::DEFAULT_WIDTH, std::max(120, screen_width - DEATH_MESSAGE_SIDE_PADDING * 2))};
    const Rect button_bounds{
        {((static_cast<float>(screen_width) - static_cast<float>(button_width)) / 2.0F),
         message_y + DEATH_BUTTON_GAP},
        button_width,
        MenuButton::DEFAULT_HEIGHT};

    retry_button_.set_bounds(button_bounds);
}

bool PlayableLevel::death_fade_finished() const
{
    return death_fade_elapsed_ >= DEATH_FADE_SECONDS;
}

void PlayableLevel::kill_player_if_below_camera()
{
    if (player_.is_dead() || !player_.has_fatal_fall_pending())
    {
        return;
    }

    if (player_is_below_camera())
    {
        player_.die();
    }
}

bool PlayableLevel::player_is_below_camera()
{
    const Rect player_bounds{player_.bounding_rect()};
    const float camera_bottom{RuntimeCtx::camera_.get_pos().y +
                              static_cast<float>(get_render_context().get_height())};

    return player_bounds.position.y > camera_bottom;
}

float PlayableLevel::death_fade_alpha() const
{
    return static_cast<float>(std::min(1.0, death_fade_elapsed_ / DEATH_FADE_SECONDS));
}

bool PlayableLevel::retry_action_was_pressed()
{
    layout_death_overlay();

    const bool enter_down{Keyboard::is_key_pressed(Keyboard::Key::Enter)};
    const bool space_down{Keyboard::is_key_pressed(Keyboard::Key::Space)};

    const bool key_pressed{death_fade_finished() && ((enter_down && !death_enter_was_down_) ||
                                                     (space_down && !death_space_was_down_))};

    death_enter_was_down_ = enter_down;
    death_space_was_down_ = space_down;

    if (!death_fade_finished())
    {
        return false;
    }

    return key_pressed || retry_button_.update();
}
