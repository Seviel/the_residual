/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_11_H
#define SRC_LEVELS_LEVEL_11_H

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

class Level_11 : public PlayableLevel
{
  public:
    Level_11()
    {
    }
    virtual ~Level_11()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_11_background.png"};
    Sprite background_sprite_{&background_texture_, 3800, 3000, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Texture foreground_texture_{"resources/gfx/level_11_foreground.png"};
    Sprite foreground_sprite_{&foreground_texture_, 3800, 3000, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_1_{{520.0F, 2740.0F}, 280.0F, 50.0F};
    Platform plat_2_{{900.0F, 2580.0F}, 280.0F, 50.0F};
    Platform plat_3_{{1380.0F, 2400.0F}, 270.0F, 50.0F};
    Platform plat_4_{{1700.0F, 2240.0F}, 250.0F, 50.0F};
    Platform plat_5_{{2180.0F, 2060.0F}, 270.0F, 50.0F};
    Platform plat_6_{{2500.0F, 1900.0F}, 250.0F, 50.0F};
    Platform plat_7_{{2850.0F, 1740.0F}, 250.0F, 50.0F};
    Platform plat_8_{{3330.0F, 1560.0F}, 270.0F, 50.0F};
    Platform plat_9_{{3050.0F, 1400.0F}, 250.0F, 50.0F};
    Platform plat_10_{{2700.0F, 1240.0F}, 250.0F, 50.0F};
    Platform plat_11_{{2300.0F, 1080.0F}, 250.0F, 50.0F};
    Platform plat_12_{{1900.0F, 920.0F}, 250.0F, 50.0F};
    Platform plat_13_{{1500.0F, 760.0F}, 250.0F, 50.0F};
    Platform plat_14_{{1900.0F, 620.0F}, 250.0F, 50.0F};
    Platform plat_15_{{2300.0F, 500.0F}, 300.0F, 50.0F};
    Platform plat_16_{{2700.0F, 380.0F}, 300.0F, 50.0F};
    Platform plat_17_{{3200.0F, 250.0F}, 400.0F, 50.0F};
    Platform floor_{{100.0F, 2900.0F}, 3600.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 3000.0F};
    Platform wall_2_{{3700.0F, 0.0F}, 100.0F, 3000.0F};
    Platform wall_3_{{1250.0F, 2400.0F}, 100.0F, 500.0F};
    Platform wall_4_{{2050.0F, 2060.0F}, 100.0F, 840.0F};
    Platform wall_5_{{3200.0F, 1560.0F}, 100.0F, 1340.0F};

    std::vector<Object*> platforms_{&plat_1_,  &plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,
                                    &plat_6_,  &plat_7_,  &plat_8_,  &plat_9_,  &plat_10_,
                                    &plat_11_, &plat_12_, &plat_13_, &plat_14_, &plat_15_,
                                    &plat_16_, &plat_17_, &floor_,   &wall_1_,  &wall_2_,
                                    &wall_3_,  &wall_4_,  &wall_5_};

    TextTrigger op_trig_1_{GameText::LVL_11_OP_1, Vector2f{2300.0F, 880.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_11_PLAYER_1, Vector2f{900.0F, 2380.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{3400.0F, 97.0F}, Levels::level_12};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_11_H
