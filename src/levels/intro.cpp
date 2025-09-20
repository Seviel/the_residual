/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "intro.h"

void IntroScreen::create()
{
}

void IntroScreen::update(double delta_time)
{
    intro_time_ += delta_time;

    rinvid::RinvidGfx::clear_screen(0.0F, 0.0F, 0.0F, 1.0F);
    background_sprite_.draw();

    if (intro_time_ > intro_duration_)
    {
        this->get_application()->set_screen(next_screen_);
    }
}

void IntroScreen::destroy()
{
}
