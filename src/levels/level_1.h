/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_1_H
#define SRC_LEVELS_LEVEL_1_H

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

class Level_1 : public PlayableLevel
{
  public:
    Level_1()
    {
    }
    virtual ~Level_1()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    void draw_parallax_background();
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_far_texture_{"resources/gfx/level_1_far.png"};
    Sprite background_far_sprite_{&background_far_texture_, 1800, 900, Vector2f{-100.0F, 0.0F},
                                  Vector2f{0.0F, 0.0F}};
    Texture background_mid_texture_{"resources/gfx/level_1_mid.png"};
    Sprite background_mid_sprite_{&background_mid_texture_, 1800, 900, Vector2f{-100.0F, 0.0F},
                                  Vector2f{0.0F, 0.0F}};
    Texture background_foreground_texture_{"resources/gfx/level_1_foreground.png"};
    Sprite background_foreground_sprite_{&background_foreground_texture_, 1800, 900,
                                         Vector2f{-100.0F, 0.0F}, Vector2f{0.0F, 0.0F}};

    Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};
    Platform floor_{{-100.0F, 700.0F}, 1700.0F, 100.0F};
    Platform wall_{{-200.0F, 0.0F}, 100.0F, 900.0F};
    Box box_{Vector2f{300.0F, 500.0F}};
    TextTrigger player_trig_1_{GameText::LVL_1_PLAYER_1, Vector2f{300.0F, 300.0F}, 50, 500};
    TextTrigger op_trig_1_{GameText::LVL_1_OP_1, Vector2f{650.0F, 300.0F}, 50, 500};
    Portal portal_{Vector2f{1350.0F, 547.0F}, Levels::level_2};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_1_H
