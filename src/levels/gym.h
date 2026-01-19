/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
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

#include "src/com_box.h"
#include "src/player.h"
#include "src/runtime_ctx.h"

using namespace rinvid;

class GymScreen : public Screen
{
  public:
    GymScreen()
    {
    }
    virtual ~GymScreen()
    {
    }
    void create() override;
    void destroy() override;

  private:
    void update(double delta_time) override;

    Texture background_texture_{"resources/gfx/main_menu.png"};
    Sprite background_sprite_{&background_texture_, 800, 600, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    ComBox com_box_{};

    Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};
    Object floor_1_{};
    Object floor_2_{};
    Object floor_3_{};
    Object wall_1_{};
    Object wall_2_{};
    Object platform_1_{};
    Camera& camera_ = RuntimeCtx::camera_;
};
