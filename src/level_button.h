/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVEL_BUTTON_H
#define SRC_LEVEL_BUTTON_H

#include <cstdint>
#include <memory>

#include <rinvid/core/sprite.h>
#include <rinvid/core/texture.h>
#include <rinvid/util/rect.h>

class LevelButton final
{
  public:
    static constexpr std::int32_t IMAGE_WIDTH{92};
    static constexpr std::int32_t IMAGE_HEIGHT{48};

    LevelButton(std::int32_t level_number, rinvid::Texture& disabled_texture);

    void set_bounds(rinvid::Rect bounds);
    void set_enabled(bool enabled);
    bool is_enabled() const;
    bool update();
    void draw();

  private:
    bool contains(rinvid::Vector2f point) const;
    void layout_sprite(rinvid::Sprite& sprite);

    rinvid::Rect bounds_{};
    std::unique_ptr<rinvid::Texture> normal_texture_{};
    std::unique_ptr<rinvid::Texture> hover_texture_{};
    std::unique_ptr<rinvid::Sprite> normal_sprite_{};
    std::unique_ptr<rinvid::Sprite> hover_sprite_{};
    std::unique_ptr<rinvid::Sprite> disabled_sprite_{};
    bool enabled_{true};
    bool hovered_{false};
    bool pressed_inside_{false};
    bool mouse_was_down_{false};
};

#endif // SRC_LEVEL_BUTTON_H
