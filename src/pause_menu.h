/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_PAUSE_MENU_H
#define SRC_PAUSE_MENU_H

#include <cstdint>
#include <memory>

#include <rinvid/core/rectangle_shape.h>
#include <rinvid/gui/label.h>

#include "src/menu_button.h"

enum class PauseAction
{
    None = 0,
    Resume,
    Restart,
    MainMenu,
    Quit
};

class PauseMenu final
{
  public:
    PauseMenu();

    PauseAction update(double delta_time);
    void draw();

    bool is_paused() const;

  private:
    void layout();
    bool pause_key_was_pressed();
    void set_paused(bool paused);

    bool paused_{false};
    bool escape_was_down_{false};
    bool p_was_down_{false};
    std::int32_t laid_out_width_{0};
    std::int32_t laid_out_height_{0};
    std::unique_ptr<rinvid::RectangleShape> overlay_{};
    std::unique_ptr<rinvid::RectangleShape> panel_{};
    rinvid::gui::Label title_;
    MenuButton resume_button_;
    MenuButton restart_button_;
    MenuButton main_menu_button_;
    MenuButton quit_button_;
};

#endif // SRC_PAUSE_MENU_H
