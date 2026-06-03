/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_MENU_BUTTON_H
#define SRC_MENU_BUTTON_H

#include <cstdint>
#include <memory>
#include <string>

#include <rinvid/core/rectangle_shape.h>
#include <rinvid/gui/label.h>
#include <rinvid/util/rect.h>

class MenuButton final
{
  public:
    static constexpr std::int32_t DEFAULT_WIDTH = 260;
    static constexpr std::int32_t DEFAULT_HEIGHT = 48;

    explicit MenuButton(std::string text);

    void set_bounds(rinvid::Rect bounds);
    void set_enabled(bool enabled);
    bool is_enabled() const;
    bool update();
    void draw();

  private:
    bool contains(rinvid::Vector2f point) const;
    void update_colors();

    rinvid::Rect bounds_{};
    std::unique_ptr<rinvid::RectangleShape> border_{};
    std::unique_ptr<rinvid::RectangleShape> body_{};
    rinvid::gui::Label label_;
    bool enabled_{true};
    bool hovered_{false};
    bool pressed_inside_{false};
    bool mouse_was_down_{false};
};

#endif // SRC_MENU_BUTTON_H
