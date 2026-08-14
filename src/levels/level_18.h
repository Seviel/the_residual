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
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_18_background.png"};
    Sprite background_sprite_{&background_texture_, 2624, 2880, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Texture foreground_texture_{"resources/gfx/level_18_foreground.png"};
    Sprite foreground_sprite_{&foreground_texture_, 4096, 4096, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_1_{{3240.0F, 300.0F}, 760.0F, 50.0F};
    Platform plat_2_{{2700.0F, 650.0F}, 1120.0F, 50.0F};
    Platform plat_3_{{2080.0F, 1000.0F}, 1910.0F, 50.0F};
    Platform plat_4_{{3260.0F, 1180.0F}, 720.0F, 50.0F};
    Platform plat_5_{{260.0F, 1350.0F}, 760.0F, 50.0F};
    Platform plat_6_{{1360.0F, 1350.0F}, 1500.0F, 50.0F};
    Platform plat_7_{{560.0F, 1700.0F}, 1600.0F, 50.0F};
    Platform plat_8_{{2460.0F, 1700.0F}, 1000.0F, 50.0F};
    Platform plat_9_{{3000.0F, 1880.0F}, 900.0F, 50.0F};
    Platform plat_10_{{100.0F, 2050.0F}, 1300.0F, 50.0F};
    Platform plat_11_{{620.0F, 2400.0F}, 2200.0F, 50.0F};
    Platform plat_12_{{300.0F, 2750.0F}, 720.0F, 50.0F};
    Platform plat_13_{{1360.0F, 2750.0F}, 1480.0F, 50.0F};
    Platform plat_14_{{380.0F, 2930.0F}, 760.0F, 50.0F};
    Platform plat_15_{{2200.0F, 3100.0F}, 1450.0F, 50.0F};
    Platform plat_16_{{1260.0F, 3450.0F}, 1600.0F, 50.0F};
    Platform plat_17_{{3020.0F, 3450.0F}, 850.0F, 50.0F};
    Platform plat_18_{{3000.0F, 3630.0F}, 820.0F, 50.0F};
    Platform plat_19_{{100.0F, 3800.0F}, 1100.0F, 50.0F};
    Platform plat_20_{{1450.0F, 3800.0F}, 760.0F, 50.0F};
    Platform floor_{{100.0F, 3996.0F}, 3900.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_2_{{3996.0F, 0.0F}, 100.0F, 4096.0F};
    Platform wall_3_{{2960.0F, 520.0F}, 110.0F, 760.0F};
    Platform wall_4_{{1840.0F, 980.0F}, 110.0F, 820.0F};
    Platform wall_5_{{880.0F, 1460.0F}, 110.0F, 760.0F};
    Platform wall_6_{{2380.0F, 2100.0F}, 110.0F, 1000.0F};
    Platform wall_7_{{3180.0F, 2920.0F}, 110.0F, 650.0F};
    Platform wall_8_{{1260.0F, 3400.0F}, 110.0F, 460.0F};

    std::vector<Object*> platforms_{
        &plat_1_,  &plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,  &plat_6_,
        &plat_7_,  &plat_8_,  &plat_9_,  &plat_10_, &plat_11_, &plat_12_,
        &plat_13_, &plat_14_, &plat_15_, &plat_16_, &plat_17_, &plat_18_,
        &plat_19_, &plat_20_, &floor_,   &wall_1_,  &wall_2_,  &wall_3_,
        &wall_4_,  &wall_5_,  &wall_6_,  &wall_7_,  &wall_8_};

    TextTrigger op_trig_1_{GameText::LVL_18_OP_1, Vector2f{2850.0F, 450.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_18_PLAYER_1, Vector2f{3500.0F, 100.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{210.0F, 3648.0F}, Levels::level_19};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_18_H
