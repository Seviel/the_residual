/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVEL_PICKER_H
#define SRC_LEVELS_LEVEL_PICKER_H

#include <array>
#include <cstdint>

#include <rinvid/core/sprite.h>
#include <rinvid/core/texture.h>
#include <rinvid/system/screen.h>

#include "src/menu_button.h"

using namespace rinvid;

class LevelPicker : public Screen
{
  public:
    LevelPicker();
    virtual ~LevelPicker()
    {
    }
    void create() override;
    void destroy() override;

  private:
    void update(double delta_time) override;
    void layout();

    Texture background_texture_{"resources/gfx/main_menu.png"};
    Sprite background_sprite_{&background_texture_, 800, 600, Vector2f{0.0F, 0.0F},
                              Vector2f{0.0F, 0.0F}};
    std::array<MenuButton, 24> level_buttons_;
    MenuButton back_button_{"Back"};
    std::int32_t laid_out_width_{0};
    std::int32_t laid_out_height_{0};
};

#endif // SRC_LEVELS_LEVEL_PICKER_H
