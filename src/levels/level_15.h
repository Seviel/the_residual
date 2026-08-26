/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_15_H
#define SRC_LEVELS_LEVEL_15_H

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

class Level_15 : public PlayableLevel
{
  public:
    Level_15() : PlayableLevel{15U}
    {
    }
    virtual ~Level_15()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Platform plat_1_{{520.0F, 1010.0F}, 620.0F, 50.0F};
    Platform plat_2_{{2780.0F, 1010.0F}, 900.0F, 50.0F};
    Platform plat_3_{{420.0F, 1180.0F}, 620.0F, 50.0F};
    Platform plat_4_{{1280.0F, 1180.0F}, 1300.0F, 50.0F};
    Platform plat_5_{{260.0F, 1350.0F}, 790.0F, 50.0F};
    Platform plat_6_{{2000.0F, 1350.0F}, 1350.0F, 50.0F};
    Platform plat_7_{{120.0F, 1520.0F}, 780.0F, 50.0F};
    Platform plat_8_{{2700.0F, 1520.0F}, 1250.0F, 50.0F};
    Platform plat_9_{{2300.0F, 1690.0F}, 1350.0F, 50.0F};
    Platform plat_10_{{240.0F, 1860.0F}, 820.0F, 50.0F};
    Platform plat_11_{{1500.0F, 1860.0F}, 1350.0F, 50.0F};
    Platform plat_12_{{140.0F, 2030.0F}, 440.0F, 50.0F};
    Platform plat_13_{{780.0F, 2030.0F}, 1350.0F, 50.0F};
    Platform plat_14_{{200.0F, 2200.0F}, 1300.0F, 50.0F};
    Platform plat_15_{{700.0F, 2370.0F}, 1350.0F, 50.0F};
    Platform plat_16_{{3150.0F, 2370.0F}, 720.0F, 50.0F};
    Platform plat_17_{{1360.0F, 2540.0F}, 1350.0F, 50.0F};
    Platform plat_18_{{3050.0F, 2540.0F}, 900.0F, 50.0F};
    Platform plat_19_{{2120.0F, 2710.0F}, 1300.0F, 50.0F};
    Platform plat_20_{{2800.0F, 2880.0F}, 1150.0F, 50.0F};
    Platform plat_21_{{2300.0F, 3050.0F}, 1620.0F, 50.0F};
    Platform plat_22_{{1550.0F, 3220.0F}, 1350.0F, 50.0F};
    Platform plat_23_{{3150.0F, 3220.0F}, 840.0F, 50.0F};
    Platform plat_24_{{120.0F, 3390.0F}, 620.0F, 50.0F};
    Platform plat_25_{{960.0F, 3390.0F}, 1300.0F, 50.0F};
    Platform plat_26_{{100.0F, 3560.0F}, 1710.0F, 50.0F};
    Platform plat_27_{{120.0F, 3730.0F}, 780.0F, 50.0F};
    Platform plat_28_{{1150.0F, 3730.0F}, 1250.0F, 50.0F};
    Platform plat_29_{{1650.0F, 3900.0F}, 1100.0F, 50.0F};
    Platform floor_{{100.0F, 3996.0F}, 3900.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_2_{{3996.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_3_{{940.0F, 1350.0F}, 110.0F, 560.0F};
    Platform wall_4_top_{{3180.0F, 1180.0F}, 110.0F, 70.0F};
    Platform wall_4_bottom_{{3180.0F, 1520.0F}, 110.0F, 220.0F};
    Platform wall_5_{{3520.0F, 2370.0F}, 110.0F, 730.0F};
    Platform wall_6_{{420.0F, 3220.0F}, 110.0F, 560.0F};

    std::vector<Object*> platforms_{&plat_1_,  &plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,
                                    &plat_6_,  &plat_7_,  &plat_8_,  &plat_9_,  &plat_10_,
                                    &plat_11_, &plat_12_, &plat_13_, &plat_14_, &plat_15_,
                                    &plat_16_, &plat_17_, &plat_18_, &plat_19_, &plat_20_,
                                    &plat_21_, &plat_22_, &plat_23_, &plat_24_, &plat_25_,
                                    &plat_26_, &plat_27_, &plat_28_, &plat_29_, &floor_,
                                    &wall_1_,  &wall_2_,  &wall_3_,  &wall_4_top_, &wall_4_bottom_,
                                    &wall_5_,  &wall_6_};

    TextTrigger op_trig_1_{GameText::LVL_15_OP_1, Vector2f{1450.0F, 3530.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_15_PLAYER_1, Vector2f{1700.0F, 3700.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{1850.0F, 1027.0F}, Levels::level_16};
    Texture background_texture_{"resources/gfx/level_15_background.png"};
    Sprite background_sprite_{&background_texture_, 2624, 2880, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Texture foreground_texture_{"resources/gfx/level_15_foreground.png"};
    Sprite foreground_sprite_{&foreground_texture_, 4096, 4096, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_15_H

