/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "main_menu.h"

#include <memory>

#include <rinvid/core/render_context.h>
#include <rinvid/system/application.h>

#include "src/levels/gym.h"
#include "src/runtime_ctx.h"

void MainMenu::create()
{
    RuntimeCtx::camera_.set_borders({-2000.0F, -2000.0F}, {2000.0F, 2000.0F});
    RuntimeCtx::camera_.set_position({0.0F, 0.0F});
    RuntimeCtx::camera_.update();

    button_play_.setup(&button_play_texture_, 100, 30, rinvid::Vector2f{225.0F, 120.0F});
    auto button_play_regions = button_play_.get_animation().split_animation_frames(120, 40, 3, 1);

    button_play_.set_idle({button_play_regions.at(0)});
    button_play_.set_hovered({button_play_regions.at(1)});
    button_play_.set_pressed({button_play_regions.at(2)});
}

void MainMenu::update(double delta_time)
{
    (void)delta_time;

    get_render_context().clear_screen(0.0F, 0.0F, 0.0F, 1.0F);
    background_sprite_.draw();
    button_play_.update();
    button_play_.draw();

    if (button_play_.was_activated())
    {
        this->get_application()->set_screen(std::make_unique<GymScreen>());
    }
}

void MainMenu::destroy()
{
}
