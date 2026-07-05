/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_4_H
#define SRC_LEVELS_LEVEL_4_H

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

class Level_4 : public PlayableLevel
{
  public:
    Level_4()
    {
    }
    virtual ~Level_4()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_far_texture_{"resources/gfx/level_4_far.png"};
    Sprite background_far_sprite_{&background_far_texture_, 1800, 1200, Vector2f{-100.0F, -100.0F},
                                  Vector2f{0.0F, 0.0F}};
    Texture background_mid_texture_{"resources/gfx/level_4_mid.png"};
    Sprite background_mid_sprite_{&background_mid_texture_, 1800, 1200, Vector2f{-100.0F, -100.0F},
                                  Vector2f{0.0F, 0.0F}};
    Texture background_foreground_texture_{"resources/gfx/level_4_foreground.png"};
    Sprite background_foreground_sprite_{&background_foreground_texture_, 1800, 1200,
                                         Vector2f{-100.0F, -100.0F}, Vector2f{0.0F, 0.0F}};


    Platform plat_1_{{0.0F, 1000.0F}, 1600.0F, 100.0F};
    Platform plat_2_{{800.0F, 800.0F}, 800.0F, 50.0F};
    Platform plat_3_{{400.0F, 600.0F}, 300.0F, 50.0F};
    Platform plat_4_{{900.0F, 600.0F}, 300.0F, 50.0F};
    Platform plat_5_{{0.0F, 400.0F}, 400.0F, 50.0F};
    Platform plat_6_{{1100.0F, 400.0F}, 400.0F, 50.0F};
    Platform plat_7_{{1300.0F, 200.0F}, 300.0F, 50.0F};

    Platform wall_1_{{-100.0F, 0.0F}, 100.0F, 1100.0F};
    Platform wall_2_{{1600.0F, 0.0F}, 100.0F, 1100.0F};

    TextTrigger op_trig_1_{GameText::LVL_4_OP_1, Vector2f{650.0F, 400.0F}, 20, 200,
                           TextRole::Operator};
    TextTrigger op_trig_2_{GameText::LVL_4_OP_2, Vector2f{200.0F, 200.0F}, 20, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_4_PLAYER_1, Vector2f{400.0F, 400.0F}, 20, 200,
                               TextRole::Player};
    TextTrigger player_trig_2_{GameText::LVL_4_PLAYER_2, Vector2f{1150.0F, 200.0F}, 20, 200,
                               TextRole::Player};
    Portal portal_{Vector2f{1400.0F, 47.0F}, Levels::level_5};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_4_H
