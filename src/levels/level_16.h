/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_16_H
#define SRC_LEVELS_LEVEL_16_H

#include <rinvid/core/camera.h>

#include "src/box.h"
#include "src/game_text.h"
#include "src/levels/levels.h"
#include "src/levels/playable_level.h"
#include "src/platform.h"
#include "src/portal.h"
#include "src/runtime_ctx.h"
#include "src/text_trigger.h"

using namespace rinvid;

class Level_16 : public PlayableLevel
{
  public:
    Level_16()
    {
    }
    virtual ~Level_16()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Platform plat_1_{{100.0F, 300.0F}, 1200.0F, 50.0F};
    Platform plat_2_{{620.0F, 650.0F}, 1450.0F, 50.0F};
    Platform plat_3_{{1450.0F, 1000.0F}, 1500.0F, 50.0F};
    Platform plat_4_{{2360.0F, 1350.0F}, 1300.0F, 50.0F};
    Platform plat_5_{{1760.0F, 1700.0F}, 1450.0F, 50.0F};
    Platform plat_6_{{720.0F, 2050.0F}, 1500.0F, 50.0F};
    Platform plat_7_{{1120.0F, 2400.0F}, 1580.0F, 50.0F};
    Platform plat_8_{{2180.0F, 2750.0F}, 1450.0F, 50.0F};
    Platform plat_9_{{3200.0F, 3100.0F}, 800.0F, 50.0F};
    Platform floor_{{100.0F, 3500.0F}, 3900.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 3600.0F};
    Platform wall_2_{{3996.0F, 0.0F}, 100.0F, 3600.0F};
    Platform wall_3_{{2140.0F, 1050.0F}, 110.0F, 500.0F};
    Platform wall_4_{{1180.0F, 2050.0F}, 110.0F, 520.0F};
    Platform wall_5_{{3080.0F, 2650.0F}, 110.0F, 600.0F};

    std::vector<Object*> platforms_{&plat_1_, &plat_2_, &plat_3_, &plat_4_, &plat_5_,
                                    &plat_6_, &plat_7_, &plat_8_, &plat_9_, &floor_,
                                    &wall_1_, &wall_2_, &wall_3_, &wall_4_, &wall_5_};

    TextTrigger op_trig_1_{GameText::LVL_16_OP_1, Vector2f{2750.0F, 800.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_16_PLAYER_1, Vector2f{500.0F, 100.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{3330.0F, 2947.0F}, Levels::level_17};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_16_H
