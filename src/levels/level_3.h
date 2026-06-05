/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_3_H
#define SRC_LEVELS_LEVEL_3_H

#include <rinvid/core/camera.h>
#include <rinvid/core/sprite.h>
#include <rinvid/core/texture.h>

#include "src/box.h"
#include "src/game_text.h"
#include "src/levels/levels.h"
#include "src/levels/playable_level.h"
#include "src/platform.h"
#include "src/player.h"
#include "src/portal.h"
#include "src/runtime_ctx.h"
#include "src/text_trigger.h"

using namespace rinvid;

class Level_3 : public PlayableLevel
{
  public:
    Level_3()
    {
    }
    virtual ~Level_3()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_3.png"};
    Sprite background_sprite_{&background_texture_, 1350, 1300, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};
    Platform plat_1_{{0.0F, 300.0F}, 500.0F, 50.0F};

    Platform plat_2_{{400.0F, 500.0F}, 400.0F, 50.0F};
    Platform plat_3_{{900.0F, 500.0F}, 250.0F, 50.0F};
    Platform plat_4_{{1250.0F, 500.0F}, 100.0F, 50.0F};

    Platform plat_5_{{1025.0F, 700.0F}, 250.0F, 50.0F};

    Platform plat_6_{{800.0F, 900.0F}, 250.0F, 50.0F};

    Platform plat_7_{{0.0F, 1100.0F}, 600.0F, 50.0F};

    Platform wall_1_{{-50.0F, 0.0F}, 100.0F, 1100.0F};
    Platform wall_2_{{1300.0F, 0.0F}, 100.0F, 1100.0F};

    TextTrigger player_trig_1_{GameText::LVL_3_PLAYER_1, Vector2f{200.0F, 0.0F}, 50, 300,
                               TextRole::Player};
    TextTrigger op_trig_1_{GameText::LVL_3_OP_1, Vector2f{600.0F, 0.0F}, 50, 500,
                           TextRole::Operator};
    Portal portal_{Vector2f{50.0F, 947.0F}, Levels::level_4};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_3_H
