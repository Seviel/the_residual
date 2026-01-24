/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "core/include/application.h"
#include "core/include/rinvid_gfx.h"
#include "core/include/screen.h"
#include "core/include/sprite.h"
#include "core/include/texture.h"
#include "platformers/include/world.h"
#include "util/include/vector2.h"

#include "levels/gym.h"
#include "levels/intro.h"
#include "levels/level_1.h"
#include "levels/main_menu.h"

using namespace rinvid;

int main()
{
    World::gravity = 2400.0F;
    Application main_app{800, 600, "TR", false};
    // Use for testing as needed
    GymScreen gym{};
    // Level_1 level_1{};
    MainMenu main_menu{&gym};
    IntroScreen intro_screen{&main_menu};
    main_app.set_screen(&intro_screen);
    main_app.set_fps(60);
    main_app.run();

    return 0;
}
