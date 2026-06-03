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
    player_.setup(&player_texture_, 52, 100, Vector2f{100.0F, 500.0F}, Vector2f{0.0F, 0.0F});

    floor_.set_movable(NOT);
    floor_.set_gravity_scale(0.0F);

    wall_.set_movable(NOT);
    wall_.set_gravity_scale(0.0F);

    RuntimeCtx::com_box()->set_text("");
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

    rinvid::World::collide(player_, floor_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, wall_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, box_, Player::separate_collision_boxes);
    rinvid::World::collide(box_, floor_);
    rinvid::World::collide(box_, wall_);
    rinvid::World::collide(player_, player_trig_1_, TextTrigger::reactivate_on_collision);
    rinvid::World::collide(player_, op_trig_1_, TextTrigger::reactivate_on_collision);
    rinvid::World::collide(player_, portal_, Portal::player_entered);

    auto camera_pos = player_.get_position();
    camera_pos.x -= get_render_context().get_width() / 2.0F;
    camera_pos.y -= get_render_context().get_height() / 2.0F;
    camera_.set_position(camera_pos);
    camera_.update();

    RuntimeCtx::com_box()->update(delta_time);
}

void Level_1::draw_level(double delta_time)
{
    draw_parallax_background();
    player_.draw(delta_time);
    box_.draw();
    portal_.draw(delta_time);
    RuntimeCtx::com_box()->draw();
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
