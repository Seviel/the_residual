/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include <memory>

#include <rinvid/platformers/world.h>
#include <rinvid/system/application.h>

#include "src/game_state.h"
#include "levels/intro.h"
#include "src/runtime_ctx.h"

using namespace rinvid;

int main()
{
    World::set_gravity(2400.0F);
    Application main_app{800, 600, "TR", false};
    GameState game_state{};
    RuntimeCtx::app_ = &main_app;
    RuntimeCtx::set_game_state(&game_state);
    main_app.set_screen(std::make_unique<IntroScreen>());
    main_app.set_fps(60);
    main_app.run();
    RuntimeCtx::set_game_state(nullptr);
    RuntimeCtx::app_ = nullptr;

    return 0;
}
