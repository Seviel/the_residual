/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "gym.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

void GymScreen::create_level()
{
    player_.setup(&player_texture_, 52, 100, Vector2f{100.0F, 100.0F}, Vector2f{0.0F, 0.0F});

    floor_1_.reset({0.0F, 534.0F});
    floor_1_.resize(221, 100);
    floor_1_.set_movable(NOT);
    floor_1_.set_gravity_scale(0.0F);

    floor_2_.reset({221.0F, 565.0F});
    floor_2_.resize(137, 100);
    floor_2_.set_movable(NOT);
    floor_2_.set_gravity_scale(0.0F);

    floor_3_.reset({358.0F, 534.0F});
    floor_3_.resize(442, 100);
    floor_3_.set_movable(NOT);
    floor_3_.set_gravity_scale(0.0F);

    wall_1_.reset({-100.0F, 0.0F});
    wall_1_.resize(100, 600);
    wall_1_.set_movable(NOT);
    wall_1_.set_gravity_scale(0.0F);

    wall_2_.reset({800.0F, 0.0F});
    wall_2_.resize(100, 600);
    wall_2_.set_movable(NOT);
    wall_2_.set_gravity_scale(0.0F);

    platform_1_.reset({0.0F, 368.0F});
    platform_1_.resize(170, 20);
    platform_1_.set_movable(NOT);
    platform_1_.set_gravity_scale(0.0F);
    platform_1_.set_allowed_collisions(UP);

    platforms_.push_back(&floor_1_);
    platforms_.push_back(&floor_2_);
    platforms_.push_back(&floor_3_);
    platforms_.push_back(&wall_1_);
    platforms_.push_back(&wall_2_);
    platforms_.push_back(&platform_1_);

    plat_.set_y_velocity(20.0F);

    camera_.set_borders({0.0F, -100.0F}, {100.0F, 0.0F});
}

void GymScreen::update_level(double delta_time)
{
    player_.update(delta_time);
    floor_1_.update(delta_time);
    floor_2_.update(delta_time);
    floor_3_.update(delta_time);
    plat_.update(delta_time);
    wall_1_.update(delta_time);
    wall_2_.update(delta_time);
    platform_1_.update(delta_time);

    rinvid::World::collide(player_, platforms_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, plat_, Player::separate_moving_plat);
    rinvid::World::collide(player_, trigger_1_, TextTrigger::reactivate_on_collision);
    rinvid::World::collide(player_, trigger_2_, TextTrigger::activate_on_collision);
    rinvid::World::collide(player_, portal_, &portal_.player_entered);

    auto camera_pos = camera_.get_pos();
    RuntimeCtx::com_box()->update(delta_time);

    camera_.update();
    camera_pos = player_.get_position();
    camera_pos.x -= get_render_context().get_width() / 2.0F;
    camera_pos.y -= get_render_context().get_height() / 2.0F;
    camera_.set_position(camera_pos);
}

void GymScreen::draw_level(double delta_time)
{
    background_sprite_.draw();
    player_.draw(delta_time);
    portal_.draw();
    plat_.draw();
    RuntimeCtx::com_box()->draw();
}

std::unique_ptr<rinvid::Screen> GymScreen::restart_level() const
{
    return Levels::gym();
}
