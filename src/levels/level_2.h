/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_2_H
#define SRC_LEVELS_LEVEL_2_H

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

class Level_2 : public PlayableLevel
{
  public:
    Level_2()
    {
    }
    virtual ~Level_2()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_2.png"};
    Sprite background_sprite_{&background_texture_, 1900, 800, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform floor_{{0.0F, 700.0F}, 900.0F, 100.0F};
    Platform plat_1_{{800.0F, 500.0F}, 600.0F, 50.0F};
    Platform plat_2_{{1300.0F, 300.0F}, 600.0F, 50.0F};
    Platform wall_{{-100.0F, 0.0F}, 100.0F, 900.0F};
    TextTrigger player_trig_1_{GameText::LVL_2_PLAYER_1, Vector2f{300.0F, 300.0F}, 50, 500,
                               TextRole::Player};
    TextTrigger op_trig_1_{GameText::LVL_2_OP_1, Vector2f{650.0F, 300.0F}, 50, 500,
                           TextRole::Operator};
    Portal portal_{Vector2f{1700.0F, 150.0F}, Levels::level_3};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_2_H
