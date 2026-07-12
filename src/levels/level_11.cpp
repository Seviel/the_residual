/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_11.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

void Level_11::create_level()
{
    setup_player(Vector2f{150.0F, 2700.0F});
    clear_com_box();
    camera_.set_borders({0.0F, 0.0F}, {3000.0F, 2400.0F});
}

void Level_11::update_level(double delta_time)
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

void Level_11::draw_level(double delta_time)
{
    player_.draw(delta_time);
    plat_1_.draw();
    plat_2_.draw();
    plat_3_.draw();
    plat_4_.draw();
    plat_5_.draw();
    plat_6_.draw();
    plat_7_.draw();
    plat_8_.draw();
    plat_9_.draw();
    plat_10_.draw();
    plat_11_.draw();
    plat_12_.draw();
    plat_13_.draw();
    plat_14_.draw();
    plat_15_.draw();
    plat_16_.draw();
    plat_17_.draw();
    floor_.draw();
    wall_1_.draw();
    wall_2_.draw();
    wall_3_.draw();
    wall_4_.draw();
    wall_5_.draw();
    portal_.draw(delta_time);
    draw_com_box();
}

std::unique_ptr<rinvid::Screen> Level_11::restart_level() const
{
    return Levels::level_11();
}
