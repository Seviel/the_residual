/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_22_H
#define SRC_LEVELS_LEVEL_22_H

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

class Level_22 : public PlayableLevel
{
  public:
    Level_22() : PlayableLevel{22U}
    {
    }
    virtual ~Level_22()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_22.png"};
    Sprite background_sprite_{&background_texture_, 2048, 900, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_1_{{100.0F, 720.0F}, 520.0F, 50.0F};
    Platform plat_2_{{700.0F, 560.0F}, 540.0F, 50.0F};
    Platform plat_3_{{1320.0F, 410.0F}, 520.0F, 50.0F};
    Platform plat_4_{{1220.0F, 760.0F}, 620.0F, 50.0F};

    Platform wall_1_{{0.0F, 0.0F}, 60.0F, 900.0F};
    Platform wall_2_{{1988.0F, 0.0F}, 60.0F, 900.0F};
    std::vector<Object*> platforms_{&plat_1_, &plat_2_, &plat_3_, &plat_4_, &wall_1_,
                                    &wall_2_};

    TextTrigger op_trig_1_{GameText::LVL_22_OP_1, Vector2f{900.0F, 360.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_22_PLAYER_1, Vector2f{300.0F, 520.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{1550.0F, 607.0F}, Levels::level_23};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_22_H
