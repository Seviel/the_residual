/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_9_H
#define SRC_LEVELS_LEVEL_9_H

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

class Level_9 : public PlayableLevel
{
  public:
    Level_9()
    {
    }
    virtual ~Level_9()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_9.png"};
    Sprite background_sprite_{&background_texture_, 800, 2400, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_2_{{430.0F, 320.0F}, 250.0F, 50.0F};
    Platform plat_3_{{120.0F, 500.0F}, 260.0F, 50.0F};
    Platform plat_4_{{430.0F, 680.0F}, 250.0F, 50.0F};
    Platform plat_5_{{120.0F, 860.0F}, 260.0F, 50.0F};
    Platform plat_6_{{430.0F, 1040.0F}, 250.0F, 50.0F};
    Platform plat_7_{{120.0F, 1220.0F}, 260.0F, 50.0F};
    Platform plat_8_{{430.0F, 1400.0F}, 250.0F, 50.0F};
    Platform plat_9_{{120.0F, 1580.0F}, 260.0F, 50.0F};
    Platform plat_10_{{430.0F, 1760.0F}, 250.0F, 50.0F};
    Platform plat_11_{{120.0F, 1940.0F}, 260.0F, 50.0F};
    Platform plat_12_{{430.0F, 2120.0F}, 250.0F, 50.0F};
    Platform floor_{{100.0F, 2300.0F}, 600.0F, 100.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 2400.0F};
    Platform wall_2_{{700.0F, 0.0F}, 100.0F, 2400.0F};
    std::vector<Object*> platforms_{&plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,  &plat_6_,
                                    &plat_7_,  &plat_8_,  &plat_9_,  &plat_10_, &plat_11_,
                                    &plat_12_, &floor_,   &wall_1_,  &wall_2_};

    TextTrigger op_trig_1_{GameText::LVL_9_OP_1, Vector2f{430.0F, 840.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_9_PLAYER_1, Vector2f{300.0F, 1740.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{520.0F, 167.0F}, Levels::level_10};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_9_H
