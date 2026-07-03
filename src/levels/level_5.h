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

    Platform plat_1_{{0.0F, 1500.0F}, 600.0F, 100.0F};
    Platform plat_2_{{800.0F, 1500.0F}, 100.0F, 100.0F};
    Platform plat_3_{{1100.0F, 1500.0F}, 300.0F, 100.0F};

    Platform plat_4_{{1400.0F, 1300.0F}, 200.0F, 50.0F};

    Platform plat_5_{{0.0F, 1100.0F}, 200.0F, 50.0F};
    Platform plat_6_{{300.0F, 1100.0F}, 200.0F, 50.0F};
    Platform plat_7_{{600.0F, 1100.0F}, 200.0F, 50.0F};
    Platform plat_8_{{900.0F, 1100.0F}, 200.0F, 50.0F};
    Platform plat_9_{{1200.0F, 1100.0F}, 200.0F, 50.0F};

    Platform plat_10_{{200.0F, 900.0F}, 1400.0F, 50.0F};

    Platform plat_11_{{0.0F, 700.0F}, 200.0F, 50.0F};
    Platform plat_12_{{300.0F, 700.0F}, 200.0F, 50.0F};
    Platform plat_13_{{600.0F, 700.0F}, 200.0F, 50.0F};
    Platform plat_14_{{900.0F, 700.0F}, 200.0F, 50.0F};
    Platform plat_15_{{1200.0F, 700.0F}, 200.0F, 50.0F};

    Platform plat_16_{{200.0F, 500.0F}, 1400.0F, 50.0F};

    Platform wall_1_{{-100.0F, 0.0F}, 100.0F, 1600.0F};
    Platform wall_2_{{1600.0F, 0.0F}, 100.0F, 1600.0F};
    std::vector<Object*> platforms_{&plat_1_,  &plat_2_,  &plat_3_,  &plat_4_,  &plat_5_,
                                    &plat_6_,  &plat_7_,  &plat_8_,  &plat_9_,  &plat_10_,
                                    &plat_11_, &plat_12_, &plat_13_, &plat_14_, &plat_15_,
                                    &plat_16_, &wall_1_,  &wall_2_};

    TextTrigger op_trig_1_{GameText::LVL_5_OP_1, Vector2f{75.0F, 75.0F}, 200, 200,
                           TextRole::Operator};
    TextTrigger player_trig_1_{GameText::LVL_5_PLAYER_1, Vector2f{75.0F, 75.0F}, 200, 200,
                               TextRole::Player};

    Portal portal_{Vector2f{1350.0F, 347.0F}, Levels::level_6};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_5_H
