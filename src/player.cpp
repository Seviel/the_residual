/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "core/include/object.h"
#include "system/include/keyboard.h"

#include "player.h"

using namespace rinvid;
using namespace rinvid::system;

Player::Player()
{
    get_animation().split_animation_frames(52, 100, 16, 1);

    auto idle_right = get_animation().get_regions({0});
    auto walking_right = get_animation().get_regions({1, 2, 3, 4, 5, 6});
    auto air_right = get_animation().get_regions({7});

    rinvid::Animation idle_right_animation{0.0F, idle_right, rinvid::AnimationMode::Normal};
    rinvid::Animation walking_right_animation{12.0F, walking_right, rinvid::AnimationMode::Looping};
    rinvid::Animation air_right_animation{0.0F, air_right, rinvid::AnimationMode::Normal};

    get_animation().add_animation("idle_right", idle_right_animation);
    get_animation().add_animation("walking_right", walking_right_animation);
    get_animation().add_animation("air_right", air_right_animation);

    auto idle_left = get_animation().get_regions({15});
    auto walking_left = get_animation().get_regions({14, 13, 12, 11, 10, 9});
    auto air_left = get_animation().get_regions({8});

    rinvid::Animation idle_left_animation{0.0F, idle_left, rinvid::AnimationMode::Normal};
    rinvid::Animation walking_left_animation{12.0F, walking_left, rinvid::AnimationMode::Looping};
    rinvid::Animation air_left_animation{0.0F, air_left, rinvid::AnimationMode::Normal};

    get_animation().add_animation("idle_left", idle_left_animation);
    get_animation().add_animation("walking_left", walking_left_animation);
    get_animation().add_animation("air_left", air_left_animation);

    get_animation().play("idle_right");
}

void Player::update(double delta_time)
{
    update_internal(delta_time);
    Object::update(delta_time);
}

void Player::update_internal(double delta_time)
{
    (void)delta_time;

    if (Keyboard::is_key_pressed(system::Keyboard::Key::Up) ||
        Keyboard::is_key_pressed(system::Keyboard::Key::W))
    {
        if (is_touching(DOWN))
        {
            set_y_velocity(-1000.0F);
        }
    }
    if (Keyboard::is_key_pressed(system::Keyboard::Key::Right) ||
        Keyboard::is_key_pressed(system::Keyboard::Key::D))
    {
        set_x_velocity(600.0F);
        get_animation().play("walking_right");
        facing_right_ = true;
    }
    else if (Keyboard::is_key_pressed(system::Keyboard::Key::Left) ||
             Keyboard::is_key_pressed(system::Keyboard::Key::A))
    {
        set_x_velocity(-600.0F);
        get_animation().play("walking_left");
        facing_right_ = false;
    }
    else
    {
        set_x_velocity(0.0F);
        if (facing_right_)
        {
            get_animation().play("idle_right");
        }
        else
        {
            get_animation().play("idle_left");
        }
    }
    if (velocity_.y != 0.0F)
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
}
