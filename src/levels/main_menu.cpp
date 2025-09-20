/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "system/include/mouse.h"

#include "main_menu.h"

void MainMenu::create()
{
    button_play_.setup(&button_play_texture_, 100, 30, rinvid::Vector2f{225.0F, 120.0F});
    auto button_play_regions = button_play_.get_animation().split_animation_frames(120, 40, 3, 1);

    button_play_.set_idle({button_play_regions.at(0)});
    button_play_.set_mouse_hovering({button_play_regions.at(1)});
    button_play_.set_clicked({button_play_regions.at(2)});
}

void MainMenu::update(double delta_time)
{
    (void)delta_time;

    rinvid::RinvidGfx::clear_screen(0.0F, 0.0F, 0.0F, 1.0F);
    background_sprite_.draw();
    button_play_.update(rinvid::system::Mouse::get_mouse_pos(get_application()));
    button_play_.draw();

    if (button_play_.just_clicked())
    {
        this->get_application()->set_screen(first_level_);
    }
}

void MainMenu::destroy()
{
}
