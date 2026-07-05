/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/portal.h"
#include "src/player.h"
#include "src/runtime_ctx.h"

#include <cstdint>
#include <vector>

using namespace rinvid;

constexpr int32_t PORTAL_WIDTH = 150;
constexpr int32_t PORTAL_HEIGHT = 153;
constexpr std::uint32_t PORTAL_FRAME_COUNT = 17U;
constexpr double PORTAL_ACTIVE_FRAMERATE = 24.0;

Portal::Portal(Vector2f position, LevelFactory level_factory)
    : tex_{"resources/gfx/portal_small.png"}, level_factory_{level_factory}
{
    setup(&tex_, PORTAL_WIDTH, PORTAL_HEIGHT, position);

    auto portal_frames =
        get_animation().split_animation_frames(PORTAL_WIDTH, PORTAL_HEIGHT, PORTAL_FRAME_COUNT, 1U);
    std::vector<Rect> active_frames{portal_frames.begin() + 1, portal_frames.end()};
    get_animation().add_animation(
        "active", Animation{PORTAL_ACTIVE_FRAMERATE, active_frames, AnimationMode::Looping});
    get_animation().play("active");

    gravity_scale_ = 0.0F;
    movable_ = false;
}

bool Portal::player_entered(Object& object_1, Object& object_2)
{
    Portal* portal = nullptr;
    Player* player = nullptr;

    portal = dynamic_cast<Portal*>(&object_1);
    player = dynamic_cast<Player*>(&object_1);
    if (!portal)
    {
        portal = dynamic_cast<Portal*>(&object_2);
    }
    if (!player)
    {
        player = dynamic_cast<Player*>(&object_2);
    }

    if (!portal || (player != nullptr && player->is_dead()))
    {
        return false;
    }

    RuntimeCtx::app_->set_screen(portal->level_factory_());

    return true;
}
