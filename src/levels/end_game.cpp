/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/end_game.h"

#include <algorithm>
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
constexpr char CONTINUATION_MESSAGE[]{"To be continued..."};
constexpr char SECONDARY_MESSAGE[]{"Maybe."};
constexpr char BOOT_MESSAGE[]{
    "DREAMSCAPE/OS 2.4.1\n"
    "Dreamscape recovery kernel 1187\n"
    "\n"
    "[  0.000 ] firmware handoff complete\n"
    "[  0.028 ] kernel image verified\n"
    "[  0.071 ] physical memory: 8192 MiB\n"
    "[  0.116 ] root volume mounted read-only\n"
    "[  0.239 ] device bus initialized\n"
    "[  0.407 ] neural interface detected\n"
    "[  0.588 ] Dreamscape runtime found\n"
    "[  0.742 ] session image recovered\n"
    "[  0.903 ] subject signal: stable\n"
    "[  1.084 ] operator channel: no carrier\n"
    "[  1.221 ] registered exit route: not found\n"
    "[  1.406 ] residual memory image preserved\n"
    "[  1.603 ] starting recovery console\n"
    "\n"
    "WARNING: UNREGISTERED GATEWAY ACCEPTED\n"
    "Automatic wake sequence suspended.\n"
    "\n"
    "recovery-node-07> _"};
constexpr std::uint32_t CONTINUATION_SIZE{38U};
constexpr std::uint32_t SECONDARY_SIZE{30U};
constexpr std::uint32_t BOOT_SIZE{20U};
constexpr std::int32_t CONTINUATION_LINE_GAP{16};
constexpr std::int32_t BOOT_PADDING{48};

const Color CONTINUATION_COLOR{0xFFFFFFFF};
const Color BOOT_COLOR{0x39FF73FF};

} // namespace

EndGameScreen::EndGameScreen(Ending ending)
    : ending_{ending},
      message_{ending == Ending::Continuation ? CONTINUATION_MESSAGE : BOOT_MESSAGE,
               FONT_PATH,
               {0.0F, 0.0F},
               ending == Ending::Continuation ? CONTINUATION_COLOR : BOOT_COLOR,
               ending == Ending::Continuation ? CONTINUATION_SIZE : BOOT_SIZE,
               0.0F,
               ending == Ending::Continuation ? rinvid::gui::LabelAlignment::Center
                                              : rinvid::gui::LabelAlignment::Left},
      secondary_message_{SECONDARY_MESSAGE,
                         FONT_PATH,
                         {0.0F, 0.0F},
                         CONTINUATION_COLOR,
                         SECONDARY_SIZE,
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

    if (ending_ == Ending::Continuation)
    {
        message_.set_bounds_width(static_cast<float>(screen_width));
        secondary_message_.set_bounds_width(static_cast<float>(screen_width));

        const float message_y{
            (static_cast<float>(screen_height) + static_cast<float>(message_.get_size())) / 2.0F};
        const float secondary_message_y{message_y + static_cast<float>(CONTINUATION_LINE_GAP) +
                                        static_cast<float>(secondary_message_.get_size())};

        message_.set_position({0.0F, message_y});
        secondary_message_.set_position({0.0F, secondary_message_y});
        return;
    }

    const std::int32_t message_width{std::max(0, screen_width - (BOOT_PADDING * 2))};
    message_.set_bounds_width(static_cast<float>(message_width));
    message_.set_position(
        {static_cast<float>(BOOT_PADDING),
         static_cast<float>(BOOT_PADDING) + static_cast<float>(message_.get_size())});
}

void EndGameScreen::draw_message()
{
    RenderContext& render_context{get_render_context()};
    const glm::mat4 old_view{render_context.get_view()};
    render_context.update_view(glm::mat4{1.0F});

    message_.draw();
    if (ending_ == Ending::Continuation)
    {
        secondary_message_.draw();
    }

    render_context.update_view(old_view);
}

void EndGameScreen::handle_pause_action(PauseAction action)
{
    switch (action)
    {
        case PauseAction::Restart:
            get_application()->set_screen(std::make_unique<EndGameScreen>(ending_));
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
