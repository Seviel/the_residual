/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_10_H
#define SRC_LEVELS_LEVEL_10_H

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

class Level_10 : public PlayableLevel
{
  public:
    Level_10()
    {
    }
    virtual ~Level_10()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_10.png"};
    Sprite background_sprite_{&background_texture_, 2800, 600, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_1_{{100.0F, 500.0F}, 450.0F, 100.0F};
    Platform plat_2_{{600.0F, 420.0F}, 250.0F, 50.0F};
    Platform plat_3_{{900.0F, 340.0F}, 250.0F, 50.0F};
    Platform plat_4_{{1210.0F, 430.0F}, 280.0F, 50.0F};
    Platform plat_5_{{1550.0F, 350.0F}, 230.0F, 50.0F};
    Platform plat_6_{{1840.0F, 450.0F}, 240.0F, 50.0F};
    Platform plat_7_{{2140.0F, 360.0F}, 240.0F, 50.0F};
    Platform plat_8_{{2410.0F, 250.0F}, 290.0F, 50.0F};

    Platform wall_1_{{0.0F, 0.0F}, 100.0F, 600.0F};
    Platform wall_2_{{2700.0F, 0.0F}, 100.0F, 600.0F};
    Platform wall_3_{{760.0F, 0.0F}, 50.0F, 260.0F};
    Platform wall_4_{{1600.0F, 400.0F}, 50.0F, 100.0F};
    Platform wall_5_{{2200.0F, 0.0F}, 50.0F, 230.0F};

    std::vector<Object*> platforms_{&plat_1_, &plat_2_, &plat_3_, &plat_4_, &plat_5_,
                                    &plat_6_, &plat_7_, &plat_8_, &wall_1_, &wall_2_,
                                    &wall_3_, &wall_4_, &wall_5_};

    TextTrigger op_trig_1_{GameText::LVL_10_OP_1, Vector2f{1550.0F, 150.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_10_PLAYER_1, Vector2f{300.0F, 300.0F}, 50, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{2460.0F, 97.0F}, Levels::level_11};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_10_H
