/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/level_button.h"

#include <algorithm>
#include <string>

#include <rinvid/system/mouse.h>

using namespace rinvid;
using namespace rinvid::system;

namespace
{

std::string level_image_path(std::int32_t level_number, const char* state_suffix)
{
    std::string path{"resources/gfx/level_picker/level_"};
    if (level_number < 10)
    {
        path += "0";
    }
    path += std::to_string(level_number);
    path += state_suffix;
    path += ".png";
    return path;
}

std::unique_ptr<Texture> load_level_texture(std::int32_t level_number,
                                            const char* state_suffix)
{
    const std::string path{level_image_path(level_number, state_suffix)};
    return std::make_unique<Texture>(path.c_str());
}

} // namespace

LevelButton::LevelButton(std::int32_t level_number, Texture& disabled_texture)
    : normal_texture_{load_level_texture(level_number, "")},
      hover_texture_{load_level_texture(level_number, "_hover")},
      clicked_texture_{load_level_texture(level_number, "_clicked")},
      normal_sprite_{std::make_unique<Sprite>(normal_texture_.get(), IMAGE_WIDTH, IMAGE_HEIGHT,
                                              Vector2f{0.0F, 0.0F})},
      hover_sprite_{std::make_unique<Sprite>(hover_texture_.get(), IMAGE_WIDTH, IMAGE_HEIGHT,
                                             Vector2f{0.0F, 0.0F})},
      clicked_sprite_{std::make_unique<Sprite>(clicked_texture_.get(), IMAGE_WIDTH, IMAGE_HEIGHT,
                                               Vector2f{0.0F, 0.0F})},
      disabled_sprite_{std::make_unique<Sprite>(&disabled_texture, IMAGE_WIDTH, IMAGE_HEIGHT,
                                                Vector2f{0.0F, 0.0F})}
{
}

void LevelButton::set_bounds(Rect bounds)
{
    bounds_ = bounds;
    layout_sprite(*normal_sprite_);
    layout_sprite(*hover_sprite_);
    layout_sprite(*clicked_sprite_);
    layout_sprite(*disabled_sprite_);
}

void LevelButton::set_enabled(bool enabled)
{
    enabled_ = enabled;
    if (!enabled_)
    {
        hovered_ = false;
        pressed_inside_ = false;
    }
}

bool LevelButton::is_enabled() const
{
    return enabled_;
}

bool LevelButton::update()
{
    const bool mouse_down{Mouse::is_button_pressed(Mouse::Left)};
    if (!enabled_)
    {
        hovered_ = false;
        pressed_inside_ = false;
        mouse_was_down_ = mouse_down;
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
    return activated;
}

void LevelButton::draw()
{
    if (!enabled_)
    {
        disabled_sprite_->draw();
    }
    else if (hovered_ && pressed_inside_ && Mouse::is_button_pressed(Mouse::Left))
    {
        clicked_sprite_->draw();
    }
    else if (hovered_)
    {
        hover_sprite_->draw();
    }
    else
    {
        normal_sprite_->draw();
    }
}

bool LevelButton::contains(Vector2f point) const
{
    return point.x >= bounds_.position.x &&
           point.x <= bounds_.position.x + static_cast<float>(bounds_.width) &&
           point.y >= bounds_.position.y &&
           point.y <= bounds_.position.y + static_cast<float>(bounds_.height);
}

void LevelButton::layout_sprite(Sprite& sprite)
{
    const float width_scale{static_cast<float>(bounds_.width) / static_cast<float>(IMAGE_WIDTH)};
    const float height_scale{static_cast<float>(bounds_.height) / static_cast<float>(IMAGE_HEIGHT)};
    const float sprite_scale{std::max(0.0F, std::min(width_scale, height_scale))};
    const float sprite_x{bounds_.position.x +
                         ((static_cast<float>(bounds_.width) - static_cast<float>(IMAGE_WIDTH)) /
                          2.0F)};
    const float sprite_y{bounds_.position.y +
                         ((static_cast<float>(bounds_.height) - static_cast<float>(IMAGE_HEIGHT)) /
                          2.0F)};
    sprite.set_position({sprite_x, sprite_y});
    sprite.set_scale(sprite_scale);
}
