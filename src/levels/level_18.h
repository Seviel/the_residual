/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_18_H
#define SRC_LEVELS_LEVEL_18_H

#include <rinvid/core/camera.h>
#include <rinvid/core/texture.h>

#include "src/box.h"
#include "src/game_text.h"
#include "src/levels/levels.h"
#include "src/levels/playable_level.h"
#include "src/platform.h"
#include "src/portal.h"
#include "src/runtime_ctx.h"
#include "src/text_trigger.h"

using namespace rinvid;

class Level_18 : public PlayableLevel
{
  public:
    Level_18()
    {
    }
    virtual ~Level_18()
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

    TextTrigger op_trig_1_{GameText::LVL_18_OP_1, Vector2f{75.0F, 75.0F}, 200, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_18_PLAYER_1, Vector2f{75.0F, 75.0F}, 200, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{1350.0F, 547.0F}, Levels::level_19};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_18_H
