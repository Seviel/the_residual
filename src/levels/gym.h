/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_GYM_H
#define SRC_LEVELS_GYM_H

#include <vector>

#include <rinvid/core/camera.h>
#include <rinvid/core/sprite.h>
#include <rinvid/core/texture.h>
#include <rinvid/platformers/object.h>

#include "src/com_box.h"
#include "src/game_text.h"
#include "src/levels/levels.h"
#include "src/levels/playable_level.h"
#include "src/platform.h"
#include "src/player.h"
#include "src/portal.h"
#include "src/runtime_ctx.h"
#include "src/text_trigger.h"

using namespace rinvid;

class GymScreen : public PlayableLevel
{
  public:
    GymScreen()
    {
    }
    virtual ~GymScreen()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/gym.png"};
    Sprite background_sprite_{&background_texture_, 800, 600, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};
    Object floor_1_{};
    Object floor_2_{};
    Object floor_3_{};
    Object wall_1_{};
    Object wall_2_{};
    Object platform_1_{};
    Platform plat_{{325.0F, 200.0F}, 100.0F, 40.0F, YES};
    std::vector<Object*> platforms_{};
    TextTrigger trigger_1_{GameText::GYM_NICE_JUMP, Vector2f{50.0F, 200.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger trigger_2_{GameText::GYM_SINGLE_TRIGGER, Vector2f{700.0F, 500.0F}, 50, 200,
                           TextRole::Operator};
    Portal portal_{Vector2f{635.0F, 175.0F}, Levels::level_5};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_GYM_H
