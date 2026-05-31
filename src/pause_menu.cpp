/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/pause_menu.h"

#include <algorithm>
#include <utility>

#include <glm/mat4x4.hpp>

#include <rinvid/core/render_context.h>
#include <rinvid/system/keyboard.h>
#include <rinvid/system/mouse.h>
#include <rinvid/util/color.h>
#include <rinvid/util/vector2.h>

using namespace rinvid;
using namespace rinvid::system;

namespace
{

constexpr const char* FONT_PATH{"resources/ttf/aquifer.ttf"};
constexpr std::int32_t BUTTON_WIDTH{260};
constexpr std::int32_t BUTTON_HEIGHT{48};
constexpr std::int32_t BUTTON_GAP{14};
constexpr std::int32_t PANEL_WIDTH{360};
constexpr std::int32_t PANEL_HEIGHT{360};

const Color TITLE_COLOR{0x5DD3B6FF};
const Color BUTTON_TEXT_COLOR{0xEAF8F5FF};
const Color BUTTON_TEXT_PRESSED_COLOR{0x071319FF};
const Color OVERLAY_COLOR{0x000000A8};
const Color PANEL_COLOR{0x081015F2};
const Color BUTTON_BORDER_COLOR{0x5DD3B6FF};
const Color BUTTON_IDLE_COLOR{0x132F3BFF};
const Color BUTTON_HOVER_COLOR{0x1E5365FF};
const Color BUTTON_PRESSED_COLOR{0x5DD3B6FF};

Vector2f center_from_bounds(const Rect bounds)
{
    return {bounds.position.x + (static_cast<float>(bounds.width) / 2.0F),
            bounds.position.y + (static_cast<float>(bounds.height) / 2.0F)};
}

} // namespace

PauseMenuButton::PauseMenuButton(std::string text)
    : label_{std::move(text), FONT_PATH, {0.0F, 0.0F}, BUTTON_TEXT_COLOR, 24,
             static_cast<float>(BUTTON_WIDTH), gui::LabelAlignment::Center}
{
}

void PauseMenuButton::set_bounds(Rect bounds)
{
    bounds_ = bounds;
    border_ = std::make_unique<RectangleShape>(center_from_bounds(bounds_), bounds_.width,
                                               bounds_.height);

    Rect body_bounds{{bounds_.position.x + 2.0F, bounds_.position.y + 2.0F}, bounds_.width - 4,
                     bounds_.height - 4};
    body_ = std::make_unique<RectangleShape>(center_from_bounds(body_bounds), body_bounds.width,
                                             body_bounds.height);

    label_.set_bounds_width(static_cast<float>(bounds_.width));
    label_.set_position({bounds_.position.x,
                         bounds_.position.y +
                             ((static_cast<float>(bounds_.height) +
                               static_cast<float>(label_.get_size())) /
                              2.0F)});
    update_colors();
}

bool PauseMenuButton::update()
{
    const bool mouse_down{Mouse::is_button_pressed(Mouse::Left)};
    hovered_ = contains(Mouse::get_mouse_pos());
    bool activated{false};

    if (mouse_down)
    {
        if (!mouse_was_down_)
        {
            pressed_inside_ = hovered_;
        }
    }
    else
    {
        activated       = mouse_was_down_ && pressed_inside_ && hovered_;
        pressed_inside_ = false;
    }

    mouse_was_down_ = mouse_down;
    update_colors();

    return activated;
}

void PauseMenuButton::draw()
{
    if (border_ != nullptr)
    {
        border_->draw();
    }

    if (body_ != nullptr)
    {
        body_->draw();
    }

    label_.draw();
}

bool PauseMenuButton::contains(Vector2f point) const
{
    return point.x >= bounds_.position.x &&
           point.x <= bounds_.position.x + static_cast<float>(bounds_.width) &&
           point.y >= bounds_.position.y &&
           point.y <= bounds_.position.y + static_cast<float>(bounds_.height);
}

void PauseMenuButton::update_colors()
{
    if (border_ != nullptr)
    {
        border_->set_color(BUTTON_BORDER_COLOR);
    }

    const bool is_pressed{hovered_ && pressed_inside_ &&
                          Mouse::is_button_pressed(Mouse::Left)};
    if (body_ != nullptr)
    {
        if (is_pressed)
        {
            body_->set_color(BUTTON_PRESSED_COLOR);
        }
        else if (hovered_)
        {
            body_->set_color(BUTTON_HOVER_COLOR);
        }
        else
        {
            body_->set_color(BUTTON_IDLE_COLOR);
        }
    }

    label_.set_color(is_pressed ? BUTTON_TEXT_PRESSED_COLOR : BUTTON_TEXT_COLOR);
}

PauseMenu::PauseMenu()
    : title_{"Paused", FONT_PATH, {0.0F, 0.0F}, TITLE_COLOR, 42, static_cast<float>(PANEL_WIDTH),
             gui::LabelAlignment::Center},
      resume_button_{"Resume"}, restart_button_{"Restart Level"}, main_menu_button_{"Main Menu"},
      quit_button_{"Quit Game"}
{
}

PauseAction PauseMenu::update(double delta_time)
{
    (void)delta_time;

    if (pause_key_was_pressed())
    {
        set_paused(!paused_);
        return paused_ ? PauseAction::None : PauseAction::Resume;
    }

    if (!paused_)
    {
        return PauseAction::None;
    }

    layout();

    if (resume_button_.update())
    {
        set_paused(false);
        return PauseAction::Resume;
    }
    if (restart_button_.update())
    {
        return PauseAction::Restart;
    }
    if (main_menu_button_.update())
    {
        return PauseAction::MainMenu;
    }
    if (quit_button_.update())
    {
        return PauseAction::Quit;
    }

    return PauseAction::None;
}

void PauseMenu::draw()
{
    if (!paused_)
    {
        return;
    }

    layout();

    RenderContext* render_context{RenderContext::get_active_context()};
    if (render_context == nullptr)
    {
        return;
    }

    const glm::mat4 old_view{render_context->get_view()};
    render_context->update_view(glm::mat4{1.0F});

    if (overlay_ != nullptr)
    {
        overlay_->draw();
    }
    if (panel_ != nullptr)
    {
        panel_->draw();
    }

    title_.draw();
    resume_button_.draw();
    restart_button_.draw();
    main_menu_button_.draw();
    quit_button_.draw();

    render_context->update_view(old_view);
}

bool PauseMenu::is_paused() const
{
    return paused_;
}

void PauseMenu::layout()
{
    RenderContext* render_context{RenderContext::get_active_context()};
    if (render_context == nullptr)
    {
        return;
    }

    const std::int32_t screen_width{render_context->get_width()};
    const std::int32_t screen_height{render_context->get_height()};
    if (screen_width == laid_out_width_ && screen_height == laid_out_height_)
    {
        return;
    }

    laid_out_width_  = screen_width;
    laid_out_height_ = screen_height;

    overlay_ = std::make_unique<RectangleShape>(
        Vector2f{static_cast<float>(screen_width) / 2.0F, static_cast<float>(screen_height) / 2.0F},
        static_cast<float>(screen_width), static_cast<float>(screen_height));
    overlay_->set_color(OVERLAY_COLOR);

    const std::int32_t panel_width{std::min(PANEL_WIDTH, screen_width - 40)};
    const std::int32_t panel_height{std::min(PANEL_HEIGHT, screen_height - 40)};
    const Vector2f panel_position{
        (static_cast<float>(screen_width) - static_cast<float>(panel_width)) / 2.0F,
        (static_cast<float>(screen_height) - static_cast<float>(panel_height)) / 2.0F};
    const Rect panel_bounds{panel_position, panel_width, panel_height};

    panel_ = std::make_unique<RectangleShape>(center_from_bounds(panel_bounds), panel_width,
                                              panel_height);
    panel_->set_color(PANEL_COLOR);

    title_.set_bounds_width(static_cast<float>(panel_width));
    title_.set_position({panel_position.x, panel_position.y + 72.0F});

    const float button_x{panel_position.x +
                         ((static_cast<float>(panel_width) - BUTTON_WIDTH) / 2.0F)};
    float button_y{panel_position.y + 114.0F};

    resume_button_.set_bounds({{button_x, button_y}, BUTTON_WIDTH, BUTTON_HEIGHT});
    button_y += BUTTON_HEIGHT + BUTTON_GAP;
    restart_button_.set_bounds({{button_x, button_y}, BUTTON_WIDTH, BUTTON_HEIGHT});
    button_y += BUTTON_HEIGHT + BUTTON_GAP;
    main_menu_button_.set_bounds({{button_x, button_y}, BUTTON_WIDTH, BUTTON_HEIGHT});
    button_y += BUTTON_HEIGHT + BUTTON_GAP;
    quit_button_.set_bounds({{button_x, button_y}, BUTTON_WIDTH, BUTTON_HEIGHT});
}

bool PauseMenu::pause_key_was_pressed()
{
    const bool escape_down{Keyboard::is_key_pressed(Keyboard::Key::Escape)};
    const bool p_down{Keyboard::is_key_pressed(Keyboard::Key::P)};
    const bool pressed{(escape_down && !escape_was_down_) || (p_down && !p_was_down_)};

    escape_was_down_ = escape_down;
    p_was_down_      = p_down;

    return pressed;
}

void PauseMenu::set_paused(bool paused)
{
    paused_ = paused;
}
