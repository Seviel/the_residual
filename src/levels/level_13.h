/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_13_H
#define SRC_LEVELS_LEVEL_13_H

#include <rinvid/core/camera.h>
#include <rinvid/core/sprite.h>
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

class Level_13 : public PlayableLevel
{
  public:
    Level_13()
    {
    }
    virtual ~Level_13()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_13.png"};
    Sprite background_sprite_{&background_texture_, 4096, 3600, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_1_{{390.0F, 3330.0F}, 1430.0F, 50.0F};
    Platform plat_2_{{260.0F, 3150.0F}, 1300.0F, 50.0F};
    Platform plat_3_{{1100.0F, 2970.0F}, 1400.0F, 50.0F};
    Platform plat_4_{{2200.0F, 2790.0F}, 1550.0F, 50.0F};
    Platform plat_5_{{920.0F, 2610.0F}, 1550.0F, 50.0F};
    Platform plat_6_{{300.0F, 2430.0F}, 1500.0F, 50.0F};
    Platform plat_7_{{760.0F, 2250.0F}, 1500.0F, 50.0F};
    Platform plat_8_{{1650.0F, 2070.0F}, 1450.0F, 50.0F};
    Platform plat_9_{{2550.0F, 1890.0F}, 1300.0F, 50.0F};
    Platform plat_10_{{2080.0F, 1710.0F}, 1450.0F, 50.0F};
    Platform plat_11_{{980.0F, 1530.0F}, 1500.0F, 50.0F};
    Platform plat_12_{{300.0F, 1350.0F}, 1450.0F, 50.0F};
    Platform plat_13_{{700.0F, 1170.0F}, 1500.0F, 50.0F};
    Platform plat_14_{{1600.0F, 990.0F}, 1500.0F, 50.0F};
    Platform plat_15_{{2550.0F, 810.0F}, 1350.0F, 50.0F};
    Platform floor_{{100.0F, 3500.0F}, 3900.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 3600.0F};
    Platform wall_2_{{3996.0F, 0.0F}, 100.0F, 3600.0F};
    Platform wall_4_{{1850.0F, 3150.0F}, 110.0F, 350.0F};
    Platform wall_5_{{3200.0F, 2070.0F}, 110.0F, 720.0F};

    std::vector<Object*> platforms_{&plat_1_,  &plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,
                                    &plat_6_,  &plat_7_,  &plat_8_,  &plat_9_,  &plat_10_,
                                    &plat_11_, &plat_12_, &plat_13_, &plat_14_, &plat_15_,
                                    &floor_,   &wall_1_,  &wall_2_,  &wall_4_,  &wall_5_};

    TextTrigger op_trig_1_{GameText::LVL_13_OP_1, Vector2f{1100.0F, 2770.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_13_PLAYER_1, Vector2f{500.0F, 3130.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{3650.0F, 657.0F}, Levels::level_14};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_13_H
