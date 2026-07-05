/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_PLAYABLE_LEVEL_H
#define SRC_LEVELS_PLAYABLE_LEVEL_H

#include <cstdint>
#include <memory>

#include <rinvid/core/rectangle_shape.h>
#include <rinvid/core/texture.h>
#include <rinvid/gui/label.h>
#include <rinvid/system/screen.h>

#include "src/menu_button.h"
#include "src/pause_menu.h"
#include "src/player.h"

class PlayableLevel : public rinvid::Screen
{
  public:
    PlayableLevel();
    virtual ~PlayableLevel() = default;

    void create() final;
    void destroy() final;

  protected:
    virtual void create_level() = 0;
    virtual void destroy_level();
    virtual void update_level(double delta_time) = 0;
    virtual void draw_level(double delta_time) = 0;
    virtual std::unique_ptr<rinvid::Screen> restart_level() const = 0;

    rinvid::Texture player_texture_{"resources/gfx/man_animated.png"};
    Player player_{};

  private:
    void update(double delta_time) final;
    void handle_pause_action(PauseAction action);
    void start_death_sequence();
    void update_death_sequence(double delta_time);
    void draw_death_overlay();
    void layout_death_overlay();
    void kill_player_if_below_camera();
    bool player_is_below_camera();
    bool death_fade_finished() const;
    float death_fade_alpha() const;
    bool retry_action_was_pressed();

    PauseMenu pause_menu_{};
    bool death_sequence_active_{false};
    double death_fade_elapsed_{0.0};
    bool death_enter_was_down_{false};
    bool death_space_was_down_{false};
    std::int32_t death_layout_width_{0};
    std::int32_t death_layout_height_{0};
    std::unique_ptr<rinvid::RectangleShape> death_overlay_{};
    rinvid::gui::Label death_message_;
    MenuButton retry_button_;
};

#endif // SRC_LEVELS_PLAYABLE_LEVEL_H
