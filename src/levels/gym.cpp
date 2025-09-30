/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "platformers/include/world.h"

#include "gym.h"

void GymScreen::create()
{
    player_.setup(&player_texture_, 52, 100, Vector2f{100.0F, 100.0F}, Vector2f{0.0F, 0.0F});

    floor_1_.reset({0.0F, 534.0F});
    floor_1_.resize(221, 100);
    floor_1_.set_movable(false);
    floor_1_.set_gravity_scale(0.0F);

    floor_2_.reset({221.0F, 565.0F});
    floor_2_.resize(137, 100);
    floor_2_.set_movable(false);
    floor_2_.set_gravity_scale(0.0F);

    floor_3_.reset({358.0F, 534.0F});
    floor_3_.resize(442, 100);
    floor_3_.set_movable(false);
    floor_3_.set_gravity_scale(0.0F);

    wall_1_.reset({-100.0F, 0.0F});
    wall_1_.resize(100, 600);
    wall_1_.set_movable(false);
    wall_1_.set_gravity_scale(0.0F);

    wall_2_.reset({800.0F, 0.0F});
    wall_2_.resize(100, 600);
    wall_2_.set_movable(false);
    wall_2_.set_gravity_scale(0.0F);

    platform_1_.reset({0.0F, 368.0F});
    platform_1_.resize(170, 20);
    platform_1_.set_movable(false);
    platform_1_.set_gravity_scale(0.0F);
    platform_1_.set_allowed_collisions(UP);
}

void GymScreen::update(double delta_time)
{
    rinvid::RinvidGfx::clear_screen(0.0F, 0.0F, 0.0F, 1.0F);

    player_.update(delta_time);
    floor_1_.update(delta_time);
    floor_2_.update(delta_time);
    floor_3_.update(delta_time);
    wall_1_.update(delta_time);
    wall_2_.update(delta_time);
    platform_1_.update(delta_time);

    rinvid::World::collide(player_, floor_1_);
    rinvid::World::collide(player_, floor_2_);
    rinvid::World::collide(player_, floor_3_);
    rinvid::World::collide(player_, wall_1_);
    rinvid::World::collide(player_, wall_2_);
    rinvid::World::collide(player_, platform_1_);

    camera_.update();
    auto camera_pos = player_.get_position();
    camera_pos.x -= RinvidGfx::get_width() / 2;
    camera_pos.y -= RinvidGfx::get_height() / 2;
    camera_.set_position(camera_pos);

    background_sprite_.draw();
    player_.draw(delta_time);
}

void GymScreen::destroy()
{
}
