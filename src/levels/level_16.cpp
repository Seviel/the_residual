/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_16.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

void Level_16::create_level()
{
    setup_player(Vector2f{100.0F, 100.0F});
    clear_com_box();
    camera_.set_borders({-2000.0F, -2000.0F}, {2000.0F, 2000.0F});
}

void Level_16::update_level(double delta_time)
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

void Level_16::draw_level(double delta_time)
{
    player_.draw(delta_time);
    plat_1_.draw();
    wall_1_.draw();
    wall_2_.draw();
    portal_.draw(delta_time);
    draw_com_box();
}

std::unique_ptr<rinvid::Screen> Level_16::restart_level() const
{
    return Levels::level_16();
}
