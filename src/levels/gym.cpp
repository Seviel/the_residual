/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "gym.h"

void GymScreen::create()
{
}

void GymScreen::update(double delta_time)
{
    (void)delta_time;

    rinvid::RinvidGfx::clear_screen(0.0F, 0.0F, 0.0F, 1.0F);
    background_sprite_.draw();
}

void GymScreen::destroy()
{
}
