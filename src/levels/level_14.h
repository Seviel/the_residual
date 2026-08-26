/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_14_H
#define SRC_LEVELS_LEVEL_14_H

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

class Level_14 : public PlayableLevel
{
  public:
    Level_14() : PlayableLevel{14U}
    {
    }
    virtual ~Level_14()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Platform plat_1_{{100.0F, 300.0F}, 1350.0F, 50.0F};
    Platform plat_2_{{900.0F, 650.0F}, 1450.0F, 50.0F};
    Platform plat_3_{{100.0F, 825.0F}, 660.0F, 50.0F};
    Platform plat_4_{{2000.0F, 1000.0F}, 440.0F, 50.0F};
    Platform plat_5_{{2550.0F, 1000.0F}, 770.0F, 50.0F};
    Platform plat_6_{{380.0F, 1175.0F}, 720.0F, 50.0F};
    Platform plat_7_{{2600.0F, 1350.0F}, 780.0F, 50.0F};
    Platform plat_8_{{3490.0F, 1350.0F}, 330.0F, 50.0F};
    Platform plat_9_{{3160.0F, 1525.0F}, 220.0F, 50.0F};
    Platform plat_10_{{3490.0F, 1525.0F}, 390.0F, 50.0F};
    Platform plat_11_{{1550.0F, 1700.0F}, 1700.0F, 50.0F};
    Platform plat_12_{{560.0F, 2050.0F}, 1680.0F, 50.0F};
    Platform plat_13_{{3260.0F, 2225.0F}, 650.0F, 50.0F};
    Platform plat_14_{{1040.0F, 2400.0F}, 1620.0F, 50.0F};
    Platform plat_15_{{100.0F, 2575.0F}, 650.0F, 50.0F};
    Platform plat_16_{{2180.0F, 2750.0F}, 1420.0F, 50.0F};
    Platform plat_17_{{2820.0F, 2925.0F}, 900.0F, 50.0F};
    Platform plat_18_{{2580.0F, 3100.0F}, 1240.0F, 50.0F};
    Platform plat_19_{{120.0F, 3275.0F}, 600.0F, 50.0F};
    Platform plat_20_{{1650.0F, 3450.0F}, 450.0F, 50.0F};
    Platform plat_21_{{2210.0F, 3450.0F}, 920.0F, 50.0F};
    Platform plat_22_{{860.0F, 3625.0F}, 620.0F, 50.0F};
    Platform plat_23_{{3000.0F, 3800.0F}, 900.0F, 50.0F};
    Platform floor_{{100.0F, 3996.0F}, 3900.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_2_{{3996.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_3_{{1550.0F, 150.0F}, 110.0F, 450.0F};
    Platform wall_4_{{2440.0F, 760.0F}, 110.0F, 520.0F};
    Platform wall_5_{{3380.0F, 1180.0F}, 110.0F, 520.0F};
    Platform wall_6_{{1300.0F, 1600.0F}, 110.0F, 450.0F};
    Platform wall_7_{{3000.0F, 2280.0F}, 110.0F, 330.0F};
    Platform wall_8_{{720.0F, 2780.0F}, 110.0F, 660.0F};
    Platform wall_9_{{2100.0F, 3310.0F}, 110.0F, 490.0F};

    std::vector<Object*> platforms_{&plat_1_,  &plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,
                                    &plat_6_,  &plat_7_,  &plat_8_,  &plat_9_,  &plat_10_,
                                    &plat_11_, &plat_12_, &plat_13_, &plat_14_, &plat_15_,
                                    &plat_16_, &plat_17_, &plat_18_, &plat_19_, &plat_20_,
                                    &plat_21_, &plat_22_, &plat_23_, &floor_,   &wall_1_,
                                    &wall_2_,  &wall_3_,  &wall_4_,  &wall_5_,  &wall_6_,
                                    &wall_7_,  &wall_8_,  &wall_9_};

    TextTrigger op_trig_1_{GameText::LVL_14_OP_1, Vector2f{1200.0F, 450.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_14_PLAYER_1, Vector2f{550.0F, 100.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{3330.0F, 3647.0F}, Levels::level_15};
    Texture background_texture_{"resources/gfx/level_14_background.png"};
    Sprite background_sprite_{&background_texture_, 2624, 2880, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Texture foreground_texture_{"resources/gfx/level_14_foreground.png"};
    Sprite foreground_sprite_{&foreground_texture_, 4096, 4096, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_14_H
