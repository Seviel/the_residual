/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include <rinvid/platformers/object.h>
#include <rinvid/platformers/world.h>
#include <rinvid/system/keyboard.h>

#include "src/platform.h"
#include "src/player.h"

using namespace rinvid;
using namespace rinvid::system;

Player::Player()
{
    get_animation().split_animation_frames(52, 100, 16, 1);

    auto idle_right = get_animation().get_regions({0});
    auto walking_right = get_animation().get_regions({1, 2, 3, 4, 5, 6});
    auto air_right = get_animation().get_regions({7});

    rinvid::Animation idle_right_animation{0.0F, idle_right, rinvid::AnimationMode::Normal};
    rinvid::Animation walking_right_animation{8.0F, walking_right, rinvid::AnimationMode::Looping};
    rinvid::Animation air_right_animation{0.0F, air_right, rinvid::AnimationMode::Normal};

    get_animation().add_animation("idle_right", idle_right_animation);
    get_animation().add_animation("walking_right", walking_right_animation);
    get_animation().add_animation("air_right", air_right_animation);

    auto idle_left = get_animation().get_regions({15});
    auto walking_left = get_animation().get_regions({14, 13, 12, 11, 10, 9});
    auto air_left = get_animation().get_regions({8});

    rinvid::Animation idle_left_animation{0.0F, idle_left, rinvid::AnimationMode::Normal};
    rinvid::Animation walking_left_animation{8.0F, walking_left, rinvid::AnimationMode::Looping};
    rinvid::Animation air_left_animation{0.0F, air_left, rinvid::AnimationMode::Normal};

    get_animation().add_animation("idle_left", idle_left_animation);
    get_animation().add_animation("walking_left", walking_left_animation);
    get_animation().add_animation("air_left", air_left_animation);

    get_animation().play("idle_right");

    x_collision_box_.set_allowed_collisions(WALL);
    x_collision_box_.resize(52, 98);
    x_collision_box_.reset(position_);

    y_collision_box_.set_allowed_collisions(UP | DOWN);
    y_collision_box_.resize(50, 100);
    y_collision_box_.reset(position_);
}

void Player::update(double delta_time)
{
    if (dead_)
    {
        return;
    }

    update_internal(delta_time);
    update_collision_boxes(delta_time);
    sync_from_collision_boxes();
    update_fall_death_state();
}

void Player::update_collision_boxes(double delta_time)
{
    x_collision_box_.reset({position_.x, position_.y + 1.0F});
    x_collision_box_.set_velocity({velocity_.x, 0.0F});
    x_collision_box_.set_acceleration({acceleration_.x, 0.0F});
    x_collision_box_.set_drag({drag_.x, 0.0F});
    x_collision_box_.set_max_velocity(max_velocity_);
    x_collision_box_.update(delta_time);

    y_collision_box_.reset({position_.x + 1.0F, position_.y});
    y_collision_box_.set_velocity({0.0F, velocity_.y});
    y_collision_box_.set_acceleration({0.0F, acceleration_.y});
    y_collision_box_.set_drag({0.0F, drag_.y});
    y_collision_box_.set_max_velocity(max_velocity_);
    y_collision_box_.set_gravity_scale(gravity_scale_);
    y_collision_box_.update(delta_time);
}

void Player::sync_from_collision_boxes()
{
    previous_position_ = position_;
    position_.x = x_collision_box_.get_position().x;
    position_.y = y_collision_box_.get_position().y;
    velocity_.x = x_collision_box_.get_x_velocity();
    velocity_.y = y_collision_box_.get_y_velocity();

    touching_ = NONE;
    if (x_collision_box_.is_touching(LEFT))
    {
        touching_ |= LEFT;
    }
    if (x_collision_box_.is_touching(RIGHT))
    {
        touching_ |= RIGHT;
    }
    if (y_collision_box_.is_touching(UP))
    {
        touching_ |= UP;
    }
    if (y_collision_box_.is_touching(DOWN))
    {
        touching_ |= DOWN;
    }

    Sprite::set_position(position_);
}

void Player::update_internal(double delta_time)
{
    (void)delta_time;

    internal_velocity_ = velocity_;

    if (Keyboard::is_key_pressed(system::Keyboard::Key::Up) ||
        Keyboard::is_key_pressed(system::Keyboard::Key::W))
    {
        if (is_touching(DOWN))
        {
            internal_velocity_.y = -1000.0F;
        }
    }
    if (Keyboard::is_key_pressed(system::Keyboard::Key::Right) ||
        Keyboard::is_key_pressed(system::Keyboard::Key::D))
    {
        internal_velocity_.x = 600.0F;
        get_animation().play("walking_right");
        facing_right_ = true;
    }
    else if (Keyboard::is_key_pressed(system::Keyboard::Key::Left) ||
             Keyboard::is_key_pressed(system::Keyboard::Key::A))
    {
        internal_velocity_.x = -600.0F;
        get_animation().play("walking_left");
        facing_right_ = false;
    }
    else
    {
        internal_velocity_.x = 0.0F;
        if (facing_right_)
        {
            get_animation().play("idle_right");
        }
        else
        {
            get_animation().play("idle_left");
        }
    }
    if (velocity_.y != 0.0F && !(touching_ & DOWN))
    {
        if (facing_right_)
        {
            get_animation().play("air_right");
        }
        else
        {
            get_animation().play("air_left");
        }
    }

    set_x_velocity(internal_velocity_.x + external_velocity_.x);
    set_y_velocity(internal_velocity_.y + external_velocity_.y);

    is_riding_ = false;
    external_velocity_.x = 0.0F;
    external_velocity_.y = 0.0F;
}

void Player::set_position(const Vector2f vector)
{
    Sprite::set_position(vector);
    x_collision_box_.reset(Vector2f{vector.x, vector.y + 1.0F});
    y_collision_box_.reset(Vector2f{vector.x + 1.0F, vector.y});
    is_tracking_fall_ = false;
    fatal_fall_pending_ = false;
    fall_start_y_ = vector.y;
}

void Player::reset(Vector2f position)
{
    Object::reset(position);
    x_collision_box_.reset(Vector2f{position.x, position.y + 1.0F});
    y_collision_box_.reset(Vector2f{position.x + 1.0F, position.y});
    set_movable(YES);
    x_collision_box_.set_movable(YES);
    y_collision_box_.set_movable(YES);
    dead_ = false;
    is_tracking_fall_ = false;
    fatal_fall_pending_ = false;
    fall_start_y_ = position.y;
}

void Player::move(const Vector2f move_vector)
{
    (void)move_vector;
    /// @todo Handle this properly
    throw "Can't use move function with player";
}

bool Player::separate_moving_plat(Object& object_1, Object& object_2)
{
    Player* player = nullptr;
    Platform* platform = nullptr;

    player = dynamic_cast<Player*>(&object_1);
    platform = dynamic_cast<Platform*>(&object_2);
    if (!player)
    {
        player = dynamic_cast<Player*>(&object_2);
        platform = dynamic_cast<Platform*>(&object_1);
    }

    if (!player || !platform)
    {
        return false;
    }

    if (player->is_dead())
    {
        return false;
    }

    player->is_riding_ = true;
    player->external_velocity_ = platform->get_velocity();
    player->external_velocity_.x *= 2.0F;
    player->external_velocity_.y *= 2.0F;

    return separate_collision_boxes(object_1, object_2);
}

bool Player::separate_collision_boxes(Object& object_1, Object& object_2)
{
    Player* player = dynamic_cast<Player*>(&object_1);
    Object* other = &object_2;

    if (!player)
    {
        player = dynamic_cast<Player*>(&object_2);
        other = &object_1;
    }

    if (!player)
    {
        return false;
    }

    bool x_separated = World::collide(player->x_collision_box_, *other);
    bool y_separated = World::collide(player->y_collision_box_, *other);

    player->sync_from_collision_boxes();
    player->update_fall_death_state();

    return x_separated || y_separated;
}

bool Player::is_dead() const
{
    return dead_;
}

bool Player::has_fatal_fall_pending() const
{
    return fatal_fall_pending_;
}

void Player::die()
{
    if (dead_)
    {
        return;
    }

    dead_ = true;
    stop_motion();
    play_death_animation();
}

void Player::update_fall_death_state()
{
    if (dead_)
    {
        return;
    }

    if (is_tracking_fall_ && (position_.y - fall_start_y_) >= FALL_DEATH_HEIGHT)
    {
        fatal_fall_pending_ = true;
    }

    if (is_touching(DOWN))
    {
        if (fatal_fall_pending_)
        {
            die();
            return;
        }

        is_tracking_fall_ = false;
        fatal_fall_pending_ = false;
        fall_start_y_ = position_.y;
        return;
    }

    if (velocity_.y > 0.0F)
    {
        if (!is_tracking_fall_)
        {
            is_tracking_fall_ = true;
            fall_start_y_ = position_.y;
        }
        return;
    }

    if (!fatal_fall_pending_)
    {
        is_tracking_fall_ = false;
        fall_start_y_ = position_.y;
    }
}

void Player::stop_motion()
{
    internal_velocity_ = {};
    external_velocity_ = {};

    set_velocity({});
    x_collision_box_.set_velocity({});
    y_collision_box_.set_velocity({});

    set_movable(NOT);
    x_collision_box_.set_movable(NOT);
    y_collision_box_.set_movable(NOT);
}

void Player::play_death_animation()
{
    // Hook the eventual death animation here once its frames are available.
}
