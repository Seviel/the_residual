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
#include <string>

#include <rinvid/core/rectangle_shape.h>
#include <rinvid/gui/label.h>
#include <rinvid/util/rect.h>

enum class PauseAction
{
    None = 0,
    Resume,
    Restart,
    MainMenu,
    Quit
};

class PauseMenuButton final
{
  public:
    explicit PauseMenuButton(std::string text);

    void set_bounds(rinvid::Rect bounds);
    bool update();
    void draw();

  private:
    bool contains(rinvid::Vector2f point) const;
    void update_colors();

    rinvid::Rect bounds_{};
    std::unique_ptr<rinvid::RectangleShape> border_{};
    std::unique_ptr<rinvid::RectangleShape> body_{};
    rinvid::gui::Label label_;
    bool hovered_{false};
    bool pressed_inside_{false};
    bool mouse_was_down_{false};
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
    PauseMenuButton resume_button_;
    PauseMenuButton restart_button_;
    PauseMenuButton main_menu_button_;
    PauseMenuButton quit_button_;
};

#endif // SRC_PAUSE_MENU_H
