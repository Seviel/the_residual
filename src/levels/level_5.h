/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_5_H
#define SRC_LEVELS_LEVEL_5_H

#include <rinvid/core/camera.h>
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

class Level_5 : public PlayableLevel
{
  public:
    Level_5()
    {
    }
    virtual ~Level_5()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};
    Platform floor_{{0.0F, 700.0F}, 1600.0F, 100.0F};
    Box box_{Vector2f{300.0F, 200.0F}};
    TextTrigger level_name_trigger_{GameText::LVL_5_OP_1, Vector2f{75.0F, 75.0F}, 200, 200,
                                    TextRole::Operator};
    Portal portal_{Vector2f{1350.0F, 547.0F}, Levels::gym};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_5_H
