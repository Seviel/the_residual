/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_6_H
#define SRC_LEVELS_LEVEL_6_H

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

class Level_6 : public PlayableLevel
{
  public:
    Level_6()
    {
    }
    virtual ~Level_6()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_far_texture_{"resources/gfx/level_6_far.png"};
    Sprite background_far_sprite_{&background_far_texture_, 1800, 1300, Vector2f{-100.0F, 0.0F},
                                  Vector2f{0.0F, 0.0F}};
    Texture background_foreground_texture_{"resources/gfx/level_6_foreground.png"};
    Sprite background_foreground_sprite_{&background_foreground_texture_, 1800, 1300,
                                         Vector2f{-100.0F, 0.0F}, Vector2f{0.0F, 0.0F}};


    Platform plat_1_{{0.0F, 1200.0F}, 1600.0F, 100.0F};

    Platform plat_2_{{0.0F, 1000.0F}, 200.0F, 50.0F};
    Platform plat_3_{{550.0F, 1000.0F}, 200.0F, 50.0F};
    Platform plat_4_{{1100.0F, 1000.0F}, 200.0F, 50.0F};

    Platform plat_5_{{300.0F, 800.0F}, 200.0F, 50.0F};
    Platform plat_6_{{850.0F, 800.0F}, 200.0F, 50.0F};
    Platform plat_7_{{1400.0F, 800.0F}, 200.0F, 50.0F};

    Platform plat_8_{{0.0F, 600.0F}, 200.0F, 50.0F};
    Platform plat_9_{{550.0F, 600.0F}, 200.0F, 50.0F};
    Platform plat_10_{{1100.0F, 600.0F}, 200.0F, 50.0F};

    Platform plat_11_{{300.0F, 400.0F}, 200.0F, 50.0F};
    Platform plat_12_{{850.0F, 400.0F}, 200.0F, 50.0F};
    Platform plat_13_{{1400.0F, 400.0F}, 200.0F, 50.0F};

    Platform plat_14_{{0.0F, 400.0F}, 200.0F, 50.0F};

    Platform wall_1_{{-100.0F, 0.0F}, 100.0F, 1300.0F};
    Platform wall_2_{{1600.0F, 0.0F}, 100.0F, 1300.0F};
    Platform wall_3_{{500.0F, 0.0F}, 50.0F, 1050.0F};
    Platform wall_4_{{1050.0F, 0.0F}, 50.0F, 1050.0F};

    std::vector<Object*> platforms_{&plat_1_,  &plat_2_,  &plat_3_, &plat_4_,  &plat_5_,  &plat_6_,
                                    &plat_7_,  &plat_8_,  &plat_9_, &plat_10_, &plat_11_, &plat_12_,
                                    &plat_13_, &plat_14_, &wall_1_, &wall_2_,  &wall_3_,  &wall_4_};

    TextTrigger op_trig_1_{GameText::LVL_6_OP_1, Vector2f{500.0F, 1000.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_6_PLAYER_1, Vector2f{1050.0F, 1000.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{0.0F, 247.0F}, Levels::level_7};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_6_H
