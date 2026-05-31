/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/playable_level.h"

#include <memory>

#include <rinvid/core/render_context.h>
#include <rinvid/system/application.h>

#include "src/levels/main_menu.h"

void PlayableLevel::create()
{
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

    const PauseAction action{pause_menu_.update(delta_time)};
    const bool        paused{pause_menu_.is_paused()};

    if (!paused)
    {
        update_level(delta_time);
    }

    draw_level(paused ? 0.0 : delta_time);

    if (paused)
    {
        pause_menu_.draw();
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
