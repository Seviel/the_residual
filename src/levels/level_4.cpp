/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_4.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

namespace
{

constexpr float BACKGROUND_X{-100.0F};
constexpr float BACKGROUND_Y{-100.0F};
constexpr float FAR_PARALLAX_FACTOR{0.15F};
constexpr float MID_PARALLAX_FACTOR{0.45F};
constexpr float FOREGROUND_PARALLAX_FACTOR{1.00F};

void draw_parallax_layer(Sprite& sprite, Vector2f camera_pos, float parallax_factor)
{
    sprite.set_position({BACKGROUND_X + camera_pos.x * (1.0F - parallax_factor),
                         BACKGROUND_Y + camera_pos.y * (1.0F - parallax_factor)});
    sprite.draw();
}

} // namespace

void Level_4::create_level()
{
    setup_player(Vector2f{100.0F, 800.0F});
    clear_com_box();
    camera_.set_borders({-100.0F, -100.0F}, {900.0F, 500.0F});
}

void Level_4::update_level(double delta_time)
{
    player_.update(delta_time);
    plat_1_.update(delta_time);
    plat_2_.update(delta_time);
    plat_3_.update(delta_time);
    plat_4_.update(delta_time);
    plat_5_.update(delta_time);
    plat_6_.update(delta_time);
    plat_7_.update(delta_time);
    wall_1_.update(delta_time);
    wall_2_.update(delta_time);

    op_trig_1_.update(delta_time);
    op_trig_2_.update(delta_time);
    player_trig_1_.update(delta_time);
    player_trig_2_.update(delta_time);

    collide_player_with(plat_1_);
    collide_player_with(plat_2_);
    collide_player_with(plat_3_);
    collide_player_with(plat_4_);
    collide_player_with(plat_5_);
    collide_player_with(plat_6_);
    collide_player_with(plat_7_);
    collide_player_with(wall_1_);
    collide_player_with(wall_2_);
    collide_player_with(op_trig_1_, TextTrigger::activate_on_collision);
    collide_player_with(op_trig_2_, TextTrigger::activate_on_collision);
    collide_player_with(player_trig_1_, TextTrigger::activate_on_collision);
    collide_player_with(player_trig_2_, TextTrigger::activate_on_collision);
    collide_player_with_portal(portal_);

    center_camera_on_player();
    update_com_box(delta_time);
}

void Level_4::draw_level(double delta_time)
{
    draw_parallax_background();
    player_.draw(delta_time);
    portal_.draw(delta_time);
    draw_com_box();
}

void Level_4::draw_parallax_background()
{
    const auto camera_pos = camera_.get_pos();

    draw_parallax_layer(background_far_sprite_, camera_pos, FAR_PARALLAX_FACTOR);
    draw_parallax_layer(background_mid_sprite_, camera_pos, MID_PARALLAX_FACTOR);
    draw_parallax_layer(background_foreground_sprite_, camera_pos, FOREGROUND_PARALLAX_FACTOR);
}

std::unique_ptr<rinvid::Screen> Level_4::restart_level() const
{
    return Levels::level_4();
}
