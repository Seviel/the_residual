/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_INTRO_H
#define SRC_LEVELS_INTRO_H

#include <rinvid/core/sprite.h>
#include <rinvid/core/texture.h>
#include <rinvid/system/screen.h>

using namespace rinvid;

class IntroScreen : public Screen
{
  public:
    IntroScreen() = default;
    virtual ~IntroScreen()
    {
    }
    void create() override;
    void destroy() override;

  private:
    void update(double delta_time) override;

    Texture background_texture_{"resources/gfx/intro.png"};
    Sprite background_sprite_{&background_texture_, 800, 600, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    const float intro_duration_ = 2.0F;
    float intro_time_ = 0.0F;
};

#endif // SRC_LEVELS_INTRO_H
