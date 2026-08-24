/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_24.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

void Level_24::create_level()
{
    setup_player(Vector2f{765.0F, 500.0F});
    clear_com_box();
    camera_.set_borders({-100.0F, 0.0F}, {900.0F, 200.0F});
}

void Level_24::update_level(double delta_time)
{
    player_.update(delta_time);
    for (auto* platform : platforms_)
    {
        platform->update(delta_time);
    }

    collide_player_with(platforms_);
    collide_player_with_portal(left_portal_);
    collide_player_with_portal(right_portal_);

    center_camera_on_player();
    update_com_box(delta_time);
}

void Level_24::draw_level(double delta_time)
{
    background_sprite_.draw();
    player_.draw(delta_time);
    left_portal_.draw(delta_time);
    right_portal_.draw(delta_time);
    draw_com_box();
}

std::unique_ptr<rinvid::Screen> Level_24::restart_level() const
{
    return Levels::level_24();
}
