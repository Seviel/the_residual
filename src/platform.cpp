/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "platform.h"

using namespace rinvid;

Platform::Platform(Vector2f position, float width, float height) : rect{position, width, height}
{
    reset(position);
    resize(width, height);
    set_movable(false);
    set_gravity_scale(0.0F);

    rect.set_color(0x888888FF);
}

void Platform::update(double delta_time)
{
    Object::update(delta_time);
    rect.set_position({position_.x + width_ / 2.0F, position_.y + height_ / 2.0F});
}

void Platform::draw()
{
    rect.draw();
}
