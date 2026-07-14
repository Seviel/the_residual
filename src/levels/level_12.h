/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_12_H
#define SRC_LEVELS_LEVEL_12_H

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

class Level_12 : public PlayableLevel
{
  public:
    Level_12()
    {
    }
    virtual ~Level_12()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Platform plat_1_{{100.0F, 300.0F}, 500.0F, 50.0F};
    Platform plat_2_{{650.0F, 450.0F}, 250.0F, 50.0F};
    Platform plat_3_{{1000.0F, 600.0F}, 250.0F, 50.0F};
    Platform plat_4_{{1450.0F, 750.0F}, 250.0F, 50.0F};
    Platform plat_5_{{1750.0F, 900.0F}, 300.0F, 50.0F};
    Platform plat_6_{{1350.0F, 1050.0F}, 250.0F, 50.0F};
    Platform plat_7_{{950.0F, 1200.0F}, 250.0F, 50.0F};
    Platform plat_8_{{550.0F, 1350.0F}, 250.0F, 50.0F};
    Platform plat_9_{{850.0F, 1500.0F}, 300.0F, 50.0F};
    Platform plat_10_{{1850.0F, 1500.0F}, 350.0F, 50.0F};
    Platform plat_11_{{1300.0F, 1600.0F}, 300.0F, 50.0F};
    Platform floor_{{100.0F, 1700.0F}, 2200.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 1800.0F};
    Platform wall_2_{{2300.0F, 0.0F}, 100.0F, 1800.0F};
    Platform wall_3_{{600.0F, 500.0F}, 80.0F, 700.0F};
    Platform wall_4_{{1300.0F, 800.0F}, 80.0F, 200.0F};
    Platform wall_5_{{1680.0F, 950.0F}, 80.0F, 400.0F};
    Platform wall_6_{{1000.0F, 1250.0F}, 80.0F, 250.0F};

    std::vector<Object*> platforms_{&plat_1_, &plat_2_, &plat_3_, &plat_4_,  &plat_5_,  &plat_6_,
                                    &plat_7_, &plat_8_, &plat_9_, &plat_10_, &plat_11_, &floor_,
                                    &wall_1_, &wall_2_, &wall_3_, &wall_4_,  &wall_5_,  &wall_6_};

    TextTrigger op_trig_1_{GameText::LVL_12_OP_1, Vector2f{1000.0F, 400.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_12_PLAYER_1, Vector2f{650.0F, 250.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{1950.0F, 1347.0F}, Levels::level_13};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_12_H
