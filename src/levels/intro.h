/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "core/include/application.h"
#include "core/include/screen.h"
#include "core/include/sprite.h"
#include "core/include/texture.h"

using namespace rinvid;

class IntroScreen : public Screen
{
  public:
    IntroScreen()
    {
    }
    virtual ~IntroScreen()
    {
    }
    void create() override;
    void destroy() override;

  private:
    void update(double delta_time) override;

    Texture background_texture{"resources/gfx/intro.png"};
    Sprite background_sprite{&background_texture, 800, 600, Vector2f{0.0F, 0.0F},
                             Vector2f{0.0F, 0.0F}};

    const float intro_duration_ = 2.0F;
    float intro_time_ = 0.0F;
};
