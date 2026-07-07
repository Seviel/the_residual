/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_6.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

namespace
{

constexpr float BACKGROUND_X{-100.0F};
constexpr float BACKGROUND_Y{0.0F};
constexpr float FAR_PARALLAX_X_FACTOR{0.18F};
constexpr float FAR_PARALLAX_Y_FACTOR{0.8F};

void draw_parallax_layer(Sprite& sprite, Vector2f camera_pos, float x_factor, float y_factor)
{
    sprite.set_position({BACKGROUND_X + camera_pos.x * (1.0F - x_factor),
                         BACKGROUND_Y + camera_pos.y * (1.0F - y_factor)});
    sprite.draw();
}

} // namespace

void Level_6::create_level()
{
    setup_player(Vector2f{1400.0F, 1000.0F});
    clear_com_box();
    camera_.set_borders({-100.0F, 0.0F}, {900.0F, 700.0F});
}

void Level_6::update_level(double delta_time)
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

void Level_6::draw_level(double delta_time)
{
    draw_parallax_background();
    player_.draw(delta_time);
    portal_.draw(delta_time);
    draw_com_box();
}

void Level_6::draw_parallax_background()
{
    const auto camera_pos = camera_.get_pos();

    draw_parallax_layer(background_far_sprite_, camera_pos, FAR_PARALLAX_X_FACTOR,
                        FAR_PARALLAX_Y_FACTOR);
    background_foreground_sprite_.set_position({BACKGROUND_X, BACKGROUND_Y});
    background_foreground_sprite_.draw();
}

std::unique_ptr<rinvid::Screen> Level_6::restart_level() const
{
    return Levels::level_6();
}
