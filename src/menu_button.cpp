/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/menu_button.h"

#include <algorithm>
#include <utility>

#include <rinvid/system/mouse.h>
#include <rinvid/util/color.h>
#include <rinvid/util/vector2.h>

using namespace rinvid;
using namespace rinvid::system;

namespace
{

constexpr const char* FONT_PATH{"resources/ttf/aquifer.ttf"};

const Color BUTTON_TEXT_COLOR{0xEAF8F5FF};
const Color BUTTON_TEXT_PRESSED_COLOR{0x071319FF};
const Color BUTTON_TEXT_DISABLED_COLOR{0x7C9297FF};
const Color BUTTON_BORDER_COLOR{0x5DD3B6FF};
const Color BUTTON_BORDER_DISABLED_COLOR{0x33525AFF};
const Color BUTTON_IDLE_COLOR{0x132F3BFF};
const Color BUTTON_HOVER_COLOR{0x1E5365FF};
const Color BUTTON_PRESSED_COLOR{0x5DD3B6FF};
const Color BUTTON_DISABLED_COLOR{0x0E1B21FF};

Vector2f center_from_bounds(const Rect bounds)
{
    return {bounds.position.x + (static_cast<float>(bounds.width) / 2.0F),
            bounds.position.y + (static_cast<float>(bounds.height) / 2.0F)};
}

} // namespace

MenuButton::MenuButton(std::string text)
    : label_{std::move(text),
             FONT_PATH,
             {0.0F, 0.0F},
             BUTTON_TEXT_COLOR,
             24,
             static_cast<float>(DEFAULT_WIDTH),
             gui::LabelAlignment::Center}
{
}

void MenuButton::set_bounds(Rect bounds)
{
    bounds_ = bounds;
    border_ = std::make_unique<RectangleShape>(center_from_bounds(bounds_), bounds_.width,
                                               bounds_.height);

    Rect body_bounds{{bounds_.position.x + 2.0F, bounds_.position.y + 2.0F},
                     std::max(0, bounds_.width - 4),
                     std::max(0, bounds_.height - 4)};
    body_ = std::make_unique<RectangleShape>(center_from_bounds(body_bounds), body_bounds.width,
                                             body_bounds.height);

    label_.set_bounds_width(static_cast<float>(bounds_.width));
    label_.set_position(
        {bounds_.position.x, bounds_.position.y + ((static_cast<float>(bounds_.height) +
                                                    static_cast<float>(label_.get_size())) /
                                                   2.0F)});
    update_colors();
}

void MenuButton::set_enabled(bool enabled)
{
    enabled_ = enabled;
    if (!enabled_)
    {
        hovered_ = false;
        pressed_inside_ = false;
    }
    update_colors();
}

bool MenuButton::is_enabled() const
{
    return enabled_;
}

bool MenuButton::update()
{
    const bool mouse_down{Mouse::is_button_pressed(Mouse::Left)};
    if (!enabled_)
    {
        hovered_ = false;
        pressed_inside_ = false;
        mouse_was_down_ = mouse_down;
        update_colors();
        return false;
    }

    hovered_ = contains(Mouse::get_mouse_pos());
    bool activated{false};

    if (mouse_down)
    {
        if (!mouse_was_down_)
        {
            pressed_inside_ = hovered_;
        }
    }
    else
    {
        activated = mouse_was_down_ && pressed_inside_ && hovered_;
        pressed_inside_ = false;
    }

    mouse_was_down_ = mouse_down;
    update_colors();

    return activated;
}

void MenuButton::draw()
{
    if (border_ != nullptr)
    {
        border_->draw();
    }

    if (body_ != nullptr)
    {
        body_->draw();
    }

    label_.draw();
}

bool MenuButton::contains(Vector2f point) const
{
    return point.x >= bounds_.position.x &&
           point.x <= bounds_.position.x + static_cast<float>(bounds_.width) &&
           point.y >= bounds_.position.y &&
           point.y <= bounds_.position.y + static_cast<float>(bounds_.height);
}

void MenuButton::update_colors()
{
    const bool is_pressed{enabled_ && hovered_ && pressed_inside_ &&
                          Mouse::is_button_pressed(Mouse::Left)};

    if (border_ != nullptr)
    {
        border_->set_color(enabled_ ? BUTTON_BORDER_COLOR : BUTTON_BORDER_DISABLED_COLOR);
    }

    if (body_ != nullptr)
    {
        if (!enabled_)
        {
            body_->set_color(BUTTON_DISABLED_COLOR);
        }
        else if (is_pressed)
        {
            body_->set_color(BUTTON_PRESSED_COLOR);
        }
        else if (hovered_)
        {
            body_->set_color(BUTTON_HOVER_COLOR);
        }
        else
        {
            body_->set_color(BUTTON_IDLE_COLOR);
        }
    }

    if (!enabled_)
    {
        label_.set_color(BUTTON_TEXT_DISABLED_COLOR);
    }
    else
    {
        label_.set_color(is_pressed ? BUTTON_TEXT_PRESSED_COLOR : BUTTON_TEXT_COLOR);
    }
}
