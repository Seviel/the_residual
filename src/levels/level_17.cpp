/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_17.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

void Level_17::create_level()
{
    setup_player(Vector2f{3760.0F, 3800.0F});
    clear_com_box();
    camera_.set_borders({0.0F, 0.0F}, {3296.0F, 3496.0F});
}

void Level_17::update_level(double delta_time)
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

void Level_17::draw_level(double delta_time)
{
    plat_1_.draw();
    plat_2_.draw();
    plat_3_.draw();
    plat_4_.draw();
    plat_5_.draw();
    plat_6_.draw();
    plat_6_right_.draw();
    plat_7_.draw();
    plat_8_.draw();
    plat_9_.draw();
    plat_10_.draw();
    plat_11_.draw();
    plat_12_.draw();
    plat_13_.draw();
    plat_14_.draw();
    plat_14_right_.draw();
    plat_15_.draw();
    plat_16_.draw();
    plat_17_.draw();
    plat_18_.draw();
    plat_19_.draw();
    plat_20_.draw();
    plat_21_.draw();
    plat_22_.draw();
    plat_23_.draw();
    plat_24_.draw();
    plat_25_.draw();
    plat_26_.draw();
    plat_27_.draw();
    plat_28_.draw();
    plat_29_.draw();
    plat_30_.draw();
    plat_31_.draw();
    floor_.draw();
    wall_1_.draw();
    wall_2_.draw();
    wall_3_.draw();
    wall_4_.draw();
    wall_5_.draw();
    player_.draw(delta_time);
    portal_.draw(delta_time);
    draw_com_box();
}

std::unique_ptr<rinvid::Screen> Level_17::restart_level() const
{
    return Levels::level_17();
}
