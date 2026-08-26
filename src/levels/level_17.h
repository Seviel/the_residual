/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_17_H
#define SRC_LEVELS_LEVEL_17_H

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

class Level_17 : public PlayableLevel
{
  public:
    Level_17() : PlayableLevel{17U}
    {
    }
    virtual ~Level_17()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_17_background.png"};
    Sprite background_sprite_{&background_texture_, 2624, 2880, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Texture foreground_texture_{"resources/gfx/level_17_foreground.png"};
    Sprite foreground_sprite_{&foreground_texture_, 4096, 4096, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_1_{{600.0F, 1180.0F}, 620.0F, 50.0F};
    Platform plat_2_{{2920.0F, 1180.0F}, 900.0F, 50.0F};
    Platform plat_3_{{100.0F, 1350.0F}, 660.0F, 50.0F};
    Platform plat_4_{{1550.0F, 1350.0F}, 1300.0F, 50.0F};
    Platform plat_5_{{3050.0F, 1350.0F}, 880.0F, 50.0F};
    Platform plat_6_{{850.0F, 1520.0F}, 230.0F, 50.0F};
    Platform plat_6_right_{{1400.0F, 1520.0F}, 750.0F, 50.0F};
    Platform plat_7_{{3000.0F, 1520.0F}, 900.0F, 50.0F};
    Platform plat_8_{{300.0F, 1690.0F}, 1200.0F, 50.0F};
    Platform plat_9_{{900.0F, 1860.0F}, 1300.0F, 50.0F};
    Platform plat_10_{{3140.0F, 1860.0F}, 760.0F, 50.0F};
    Platform plat_11_{{1600.0F, 2030.0F}, 1280.0F, 50.0F};
    Platform plat_12_{{3100.0F, 2030.0F}, 840.0F, 50.0F};
    Platform plat_13_{{160.0F, 2200.0F}, 680.0F, 50.0F};
    Platform plat_14_{{2350.0F, 2200.0F}, 830.0F, 50.0F};
    Platform plat_14_right_{{3520.0F, 2200.0F}, 460.0F, 50.0F};
    Platform plat_15_{{220.0F, 2370.0F}, 760.0F, 50.0F};
    Platform plat_16_{{2750.0F, 2370.0F}, 1250.0F, 50.0F};
    Platform plat_17_{{500.0F, 2540.0F}, 760.0F, 50.0F};
    Platform plat_18_{{2050.0F, 2540.0F}, 1350.0F, 50.0F};
    Platform plat_19_{{1300.0F, 2710.0F}, 1350.0F, 50.0F};
    Platform plat_20_{{760.0F, 2880.0F}, 1300.0F, 50.0F};
    Platform plat_21_{{180.0F, 3050.0F}, 1250.0F, 50.0F};
    Platform plat_22_{{760.0F, 3220.0F}, 1300.0F, 50.0F};
    Platform plat_23_{{3120.0F, 3220.0F}, 760.0F, 50.0F};
    Platform plat_24_{{1450.0F, 3390.0F}, 1300.0F, 50.0F};
    Platform plat_25_{{3200.0F, 3390.0F}, 760.0F, 50.0F};
    Platform plat_26_{{260.0F, 3560.0F}, 880.0F, 50.0F};
    Platform plat_27_{{2200.0F, 3560.0F}, 1050.0F, 50.0F};
    Platform plat_28_{{3450.0F, 3560.0F}, 530.0F, 50.0F};
    Platform plat_29_{{120.0F, 3730.0F}, 760.0F, 50.0F};
    Platform plat_30_{{2780.0F, 3730.0F}, 900.0F, 50.0F};
    Platform plat_31_{{3280.0F, 3900.0F}, 700.0F, 50.0F};
    Platform floor_{{100.0F, 3996.0F}, 3900.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_2_{{3996.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_3_{{1080.0F, 1180.0F}, 110.0F, 560.0F};
    Platform wall_4_{{3380.0F, 1860.0F}, 110.0F, 560.0F};
    Platform wall_5_{{520.0F, 2370.0F}, 110.0F, 730.0F};

    std::vector<Object*> platforms_{
        &plat_1_,  &plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,  &plat_6_,  &plat_7_,
        &plat_6_right_, &plat_8_,  &plat_9_,  &plat_10_, &plat_11_, &plat_12_, &plat_13_,
        &plat_14_, &plat_14_right_,
        &plat_15_, &plat_16_, &plat_17_, &plat_18_, &plat_19_, &plat_20_, &plat_21_,
        &plat_22_, &plat_23_, &plat_24_, &plat_25_, &plat_26_, &plat_27_, &plat_28_,
        &plat_29_, &plat_30_, &plat_31_, &floor_,   &wall_1_,  &wall_2_,  &wall_3_,
        &wall_4_,  &wall_5_};

    TextTrigger op_trig_1_{GameText::LVL_17_OP_1, Vector2f{2800.0F, 3530.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_17_PLAYER_1, Vector2f{3550.0F, 3700.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{2200.0F, 1197.0F}, Levels::level_18};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_17_H
