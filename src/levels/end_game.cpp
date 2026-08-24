/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/end_game.h"

#include <memory>

#include <glm/mat4x4.hpp>

#include <rinvid/core/render_context.h>
#include <rinvid/system/application.h>
#include <rinvid/system/keyboard.h>
#include <rinvid/util/color.h>

#include "src/levels/main_menu.h"

using namespace rinvid;
using namespace rinvid::system;

namespace
{

constexpr const char* FONT_PATH{"resources/ttf/aquifer.ttf"};
constexpr std::uint32_t MESSAGE_SIZE{38U};

const Color MESSAGE_COLOR{0xFFFFFFFF};

} // namespace

EndGameScreen::EndGameScreen()
    : message_{"To be continued...",
               FONT_PATH,
               {0.0F, 0.0F},
               MESSAGE_COLOR,
               MESSAGE_SIZE,
               0.0F,
               rinvid::gui::LabelAlignment::Center}
{
}

void EndGameScreen::create()
{
    laid_out_width_ = 0;
    laid_out_height_ = 0;
}

void EndGameScreen::destroy()
{
}

void EndGameScreen::update(double delta_time)
{
    get_render_context().clear_screen(0.0F, 0.0F, 0.0F, 1.0F);

    if (Keyboard::is_key_pressed(Keyboard::Key::Escape) ||
        Keyboard::is_key_pressed(Keyboard::Key::Enter))
    {
        get_application()->set_screen(std::make_unique<MainMenu>());
        return;
    }

    const PauseAction action{pause_menu_.update(delta_time)};

    layout();
    draw_message();

    if (pause_menu_.is_paused())
    {
        pause_menu_.draw();
    }

    handle_pause_action(action);
}

void EndGameScreen::layout()
{
    const std::int32_t screen_width{get_render_context().get_width()};
    const std::int32_t screen_height{get_render_context().get_height()};
    if (screen_width == laid_out_width_ && screen_height == laid_out_height_)
    {
        return;
    }

    laid_out_width_ = screen_width;
    laid_out_height_ = screen_height;

    message_.set_bounds_width(static_cast<float>(screen_width));
    const float message_y{(static_cast<float>(screen_height) +
                           static_cast<float>(message_.get_size())) /
                          2.0F};
    message_.set_position({0.0F, message_y});
}

void EndGameScreen::draw_message()
{
    RenderContext& render_context{get_render_context()};
    const glm::mat4 old_view{render_context.get_view()};
    render_context.update_view(glm::mat4{1.0F});

    message_.draw();

    render_context.update_view(old_view);
}

void EndGameScreen::handle_pause_action(PauseAction action)
{
    switch (action)
    {
        case PauseAction::Restart:
            get_application()->set_screen(std::make_unique<EndGameScreen>());
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
