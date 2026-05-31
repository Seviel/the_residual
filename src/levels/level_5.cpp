/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_5.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

void Level_5::create_level()
{
    player_.setup(&player_texture_, 52, 100, Vector2f{100.0F, 100.0F}, Vector2f{0.0F, 0.0F});

    floor_.set_movable(NOT);
    floor_.set_gravity_scale(0.0F);

    RuntimeCtx::com_box()->set_text("");
    camera_.set_borders({-2000.0F, -2000.0F}, {2000.0F, 2000.0F});
}

void Level_5::update_level(double delta_time)
{
    player_.update(delta_time);
    floor_.update(delta_time);
    box_.update(delta_time);
    level_name_trigger_.update(delta_time);

    rinvid::World::collide(player_, floor_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, box_, Player::separate_collision_boxes);
    rinvid::World::collide(box_, floor_);
    rinvid::World::collide(player_, box_, Player::separate_collision_boxes);
    rinvid::World::collide(box_, floor_);
    rinvid::World::collide(player_, level_name_trigger_, TextTrigger::activate_on_collision);
    rinvid::World::collide(player_, portal_, Portal::player_entered);

    auto camera_pos = camera_.get_pos();
    RuntimeCtx::com_box()->update(delta_time);

    camera_.update();
    camera_pos = player_.get_position();
    camera_pos.x -= get_render_context().get_width() / 2.0F;
    camera_pos.y -= get_render_context().get_height() / 2.0F;
    camera_.set_position(camera_pos);
}

void Level_5::draw_level(double delta_time)
{
    player_.draw(delta_time);
    floor_.draw();
    box_.draw();
    portal_.draw();
    RuntimeCtx::com_box()->draw();
}

std::unique_ptr<rinvid::Screen> Level_5::restart_level() const
{
    return Levels::level_5();
}
