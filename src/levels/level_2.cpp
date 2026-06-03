/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_2.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

void Level_2::create_level()
{
    player_.setup(&player_texture_, 52, 100, Vector2f{100.0F, 500.0F}, Vector2f{0.0F, 0.0F});

    floor_.set_movable(NOT);
    floor_.set_gravity_scale(0.0F);

    plat_1_.set_movable(NOT);
    plat_1_.set_gravity_scale(0.0F);

    plat_2_.set_movable(NOT);
    plat_2_.set_gravity_scale(0.0F);

    wall_.set_movable(NOT);
    wall_.set_gravity_scale(0.0F);

    RuntimeCtx::com_box()->set_text("");
    camera_.set_borders({0.0F, 0.0F}, {1100.0F, 200.0F});
}

void Level_2::update_level(double delta_time)
{
    player_.update(delta_time);
    floor_.update(delta_time);
    plat_1_.update(delta_time);
    plat_2_.update(delta_time);
    wall_.update(delta_time);
    player_trig_1_.update(delta_time);
    op_trig_1_.update(delta_time);

    rinvid::World::collide(player_, floor_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, plat_1_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, plat_2_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, wall_, Player::separate_collision_boxes);
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

void Level_2::draw_level(double delta_time)
{
    background_sprite_.draw();
    player_.draw(delta_time);
    portal_.draw(delta_time);
    RuntimeCtx::com_box()->draw();
}

std::unique_ptr<rinvid::Screen> Level_2::restart_level() const
{
    return Levels::level_2();
}
