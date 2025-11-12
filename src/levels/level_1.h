/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "core/include/camera.h"
#include "core/include/object.h"
#include "core/include/screen.h"
#include "core/include/sprite.h"
#include "core/include/texture.h"

#include "src/platform.h"
#include "src/player.h"

using namespace rinvid;

class Level_1 : public Screen
{
  public:
    Level_1()
    {
    }
    virtual ~Level_1()
    {
    }
    void create() override;
    void destroy() override;

  private:
    void update(double delta_time) override;

    Texture text_box_tex_{"resources/gfx/text_box.png"};
    Sprite text_box_{&text_box_tex_, 724, 124, Vector2f{0.0F, 0.0F}, Vector2f{0.0F, 0.0F}};

    Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};
    Platform floor{{0.0F, 700.0F}, 800.0F, 100.0F};
    Camera camera_{};
};
