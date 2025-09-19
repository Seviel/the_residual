/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
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
#include "util/include/vector2.h"

#include "levels/intro.h"
#include "levels/main_menu.h"

using namespace rinvid;

int main()
{
    Application main_app{800, 600, "TR", false};
    MainMenu main_menu{};
    IntroScreen intro_screen{&main_menu};
    main_app.set_screen(&intro_screen);
    main_app.set_fps(60);
    main_app.run();

    return 0;
}
