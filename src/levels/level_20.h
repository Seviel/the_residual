/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_20_H
#define SRC_LEVELS_LEVEL_20_H

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

class Level_20 : public PlayableLevel
{
  public:
    Level_20() : PlayableLevel{20U}
    {
    }
    virtual ~Level_20()
    {
    }

  private:
    void create_level() override;
    void update_level(double delta_time) override;
    void draw_level(double delta_time) override;
    std::unique_ptr<rinvid::Screen> restart_level() const override;

    Texture background_texture_{"resources/gfx/level_20.png"};
    Sprite background_sprite_{&background_texture_, 1800, 900, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};

    Platform plat_1_{{80.0F, 780.0F}, 450.0F, 50.0F};
    Platform plat_2_{{650.0F, 640.0F}, 470.0F, 50.0F};
    Platform plat_3_{{120.0F, 450.0F}, 470.0F, 50.0F};
    Platform plat_4_{{750.0F, 360.0F}, 500.0F, 50.0F};
    Platform plat_5_{{1320.0F, 240.0F}, 360.0F, 50.0F};

    Platform wall_1_{{0.0F, 0.0F}, 60.0F, 900.0F};
    Platform wall_2_{{1740.0F, 0.0F}, 60.0F, 900.0F};
    std::vector<Object*> platforms_{&plat_1_, &plat_2_, &plat_3_, &plat_4_,
                                    &plat_5_, &wall_1_, &wall_2_};

    TextTrigger op_trig_1_{GameText::LVL_20_OP_1, Vector2f{260.0F, 580.0F}, 50, 200,
                           TextRole::Operator};
    TextTrigger op_trig_2_{GameText::LVL_20_OP_2, Vector2f{820.0F, 160.0F}, 50, 200,
                           TextRole::Operator};

    Portal portal_{Vector2f{1480.0F, 87.0F}, Levels::level_21};
    Camera& camera_ = RuntimeCtx::camera_;
};

#endif // SRC_LEVELS_LEVEL_20_H
