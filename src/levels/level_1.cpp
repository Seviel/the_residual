/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_1.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

namespace
{

constexpr float BACKGROUND_X{-100.0F};
constexpr float BACKGROUND_Y{0.0F};
constexpr float FAR_PARALLAX_FACTOR{0.20F};
constexpr float MID_PARALLAX_FACTOR{0.55F};
constexpr float FOREGROUND_PARALLAX_FACTOR{1.00F};

void draw_parallax_layer(Sprite& sprite, Vector2f camera_pos, float parallax_factor)
{
    // Parallax factor applied only to the x axis in this case.
    sprite.set_position({BACKGROUND_X + camera_pos.x * (1.0F - parallax_factor), BACKGROUND_Y});
    sprite.draw();
}

} // namespace

void Level_1::create_level()
{
    setup_player(Vector2f{100.0F, 500.0F});
    floor_.set_movable(NOT);
    floor_.set_gravity_scale(0.0F);

    wall_.set_movable(NOT);
    wall_.set_gravity_scale(0.0F);

    clear_com_box();
    camera_.set_borders({-100.0F, 0.0F}, {900.0F, 150.0F});
}

void Level_1::update_level(double delta_time)
{
    player_.update(delta_time);
    floor_.update(delta_time);
    wall_.update(delta_time);
    box_.update(delta_time);
    player_trig_1_.update(delta_time);
    op_trig_1_.update(delta_time);

    collide_player_with(floor_);
    collide_player_with(wall_);
    collide_player_with(box_);
    rinvid::World::collide(box_, floor_);
    rinvid::World::collide(box_, wall_);
    collide_player_with(player_trig_1_, TextTrigger::reactivate_on_collision);
    collide_player_with(op_trig_1_, TextTrigger::reactivate_on_collision);
    collide_player_with_portal(portal_);

    center_camera_on_player();
    update_com_box(delta_time);
}

void Level_1::draw_level(double delta_time)
{
    draw_parallax_background();
    player_.draw(delta_time);
    box_.draw();
    portal_.draw(delta_time);
    draw_com_box();
}

void Level_1::draw_parallax_background()
{
    const auto camera_pos = camera_.get_pos();

    draw_parallax_layer(background_far_sprite_, camera_pos, FAR_PARALLAX_FACTOR);
    draw_parallax_layer(background_mid_sprite_, camera_pos, MID_PARALLAX_FACTOR);
    draw_parallax_layer(background_foreground_sprite_, camera_pos, FOREGROUND_PARALLAX_FACTOR);
}

std::unique_ptr<rinvid::Screen> Level_1::restart_level() const
{
    return Levels::level_1();
}
