/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "platformers/include/world.h"

#include "level_1.h"

void Level_1::create()
{
    player_.setup(&player_texture_, 52, 100, Vector2f{100.0F, 100.0F}, Vector2f{0.0F, 0.0F});

    floor.reset({0.0F, 700.0F});
    floor.resize(800, 100);
    floor.set_movable(false);
    floor.set_gravity_scale(0.0F);
}

void Level_1::update(double delta_time)
{
    rinvid::RinvidGfx::clear_screen(0.0F, 0.0F, 0.0F, 1.0F);

    player_.update(delta_time);
    floor.update(delta_time);

    rinvid::World::collide(player_, floor);

    auto camera_pos = camera_.get_pos();
    text_box_.set_position({camera_pos.x + 38, camera_pos.y + 20});

    camera_.update();
    camera_pos = player_.get_position();
    camera_pos.x -= RinvidGfx::get_width() / 2;
    camera_pos.y -= RinvidGfx::get_height() / 2;
    camera_.set_position(camera_pos);

    player_.draw(delta_time);
    text_box_.draw();
    floor.draw();
}

void Level_1::destroy()
{
}
