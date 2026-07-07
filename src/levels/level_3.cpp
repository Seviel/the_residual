/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_3.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

void Level_3::create_level()
{
    setup_player(Vector2f{100.0F, 100.0F});
    clear_com_box();
    camera_.set_borders({0.0F, 0.0F}, {550.0F, 700.0F});
}

void Level_3::update_level(double delta_time)
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
    player_trig_1_.update(delta_time);
    op_trig_1_.update(delta_time);

    collide_player_with(plat_1_);
    collide_player_with(plat_2_);
    collide_player_with(plat_3_);
    collide_player_with(plat_4_);
    collide_player_with(plat_5_);
    collide_player_with(plat_6_);
    collide_player_with(plat_7_);
    collide_player_with(wall_1_);
    collide_player_with(wall_2_);
    collide_player_with(player_trig_1_, TextTrigger::reactivate_on_collision);
    collide_player_with(op_trig_1_, TextTrigger::reactivate_on_collision);
    collide_player_with_portal(portal_);

    center_camera_on_player();
    update_com_box(delta_time);
}

void Level_3::draw_level(double delta_time)
{
    background_sprite_.draw();
    player_.draw(delta_time);
    portal_.draw(delta_time);
    draw_com_box();
}

std::unique_ptr<rinvid::Screen> Level_3::restart_level() const
{
    return Levels::level_3();
}
