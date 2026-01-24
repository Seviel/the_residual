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

#include "src/platform.h"
#include "src/player.h"
#include "src/runtime_ctx.h"

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

    Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};
    Platform floor{{0.0F, 700.0F}, 800.0F, 100.0F};
    Camera& camera_ = RuntimeCtx::camera_;
};
