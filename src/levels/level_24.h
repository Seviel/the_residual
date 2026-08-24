/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_24_H
#define SRC_LEVELS_LEVEL_24_H

#include <rinvid/core/camera.h>
#include <rinvid/core/texture.h>

#include "src/box.h"
#include "src/levels/levels.h"
#include "src/levels/playable_level.h"
#include "src/platform.h"
#include "src/portal.h"
#include "src/runtime_ctx.h"

using namespace rinvid;

class Level_24 : public PlayableLevel
{
  public:
    Level_24()
    {
    }
    virtual ~Level_24()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Platform plat_1_{{0.0F, 700.0F}, 1600.0F, 100.0F};
    Platform wall_1_{{-100.0F, 0.0F}, 100.0F, 800.0F};
    Platform wall_2_{{1600.0F, 0.0F}, 100.0F, 800.0F};
    std::vector<Object*> platforms_{&plat_1_, &wall_1_, &wall_2_};

    Portal left_portal_{Vector2f{0.0F, 547.0F}, Levels::gym};
    Portal right_portal_{Vector2f{1450.0F, 547.0F}, Levels::gym};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_24_H
