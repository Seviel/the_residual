/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_14.h"

#include <cmath>

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

namespace
{
constexpr float BACKGROUND_X{0.0F};
constexpr float BACKGROUND_Y{0.0F};
constexpr float BACKGROUND_PARALLAX_X_FACTOR{0.55F};
constexpr float BACKGROUND_PARALLAX_Y_FACTOR{0.65F};

void draw_parallax_layer(Sprite& sprite, Vector2f camera_pos, float x_factor, float y_factor)
{
    sprite.set_position(
        {BACKGROUND_X + std::round(camera_pos.x * (1.0F - x_factor)),
         BACKGROUND_Y + std::round(camera_pos.y * (1.0F - y_factor))});
    sprite.draw();
}
} // namespace

void Level_14::create_level()
{
    setup_player(Vector2f{180.0F, 200.0F});
    clear_com_box();
    camera_.set_borders({0.0F, 0.0F}, {3296.0F, 3496.0F});
}

void Level_14::update_level(double delta_time)
{
    player_.update(delta_time);
    for (auto* platform : platforms_)
    {
        platform->update(delta_time);
    }
    player_trig_1_.update(delta_time);
    op_trig_1_.update(delta_time);

    collide_player_with(platforms_);
    collide_player_with(player_trig_1_, TextTrigger::reactivate_on_collision);
    collide_player_with(op_trig_1_, TextTrigger::reactivate_on_collision);
    collide_player_with_portal(portal_);

    center_camera_on_player();
    update_com_box(delta_time);
}

void Level_14::draw_level(double delta_time)
{
    draw_parallax_background();
    player_.draw(delta_time);
    portal_.draw(delta_time);
    draw_com_box();
}

void Level_14::draw_parallax_background()
{
    const auto camera_pos = camera_.get_pos();
    draw_parallax_layer(background_sprite_, camera_pos, BACKGROUND_PARALLAX_X_FACTOR,
                        BACKGROUND_PARALLAX_Y_FACTOR);
    foreground_sprite_.set_position({BACKGROUND_X, BACKGROUND_Y});
    foreground_sprite_.draw();
}

std::unique_ptr<rinvid::Screen> Level_14::restart_level() const
{
    return Levels::level_14();
}

