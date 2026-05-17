/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_MAIN_MENU_H
#define SRC_LEVELS_MAIN_MENU_H

#include <rinvid/core/sprite.h>
#include <rinvid/core/texture.h>
#include <rinvid/gui/button.h>
#include <rinvid/system/screen.h>

using namespace rinvid;

class MainMenu : public Screen
{
  public:
    MainMenu() = default;
    virtual ~MainMenu()
    {
    }
    void create() override;
    void destroy() override;

  private:
    void update(double delta_time) override;

    Texture background_texture_{"resources/gfx/main_menu.png"};
    Sprite background_sprite_{&background_texture_, 800, 600, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    Texture button_play_texture_{"resources/gfx/gui/btn_play.png"};
    rinvid::gui::Button button_play_{};
};

#endif // SRC_LEVELS_MAIN_MENU_H
