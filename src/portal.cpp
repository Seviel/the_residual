/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/portal.h"
#include "src/runtime_ctx.h"

using namespace rinvid;

constexpr int32_t PORTAL_WIDTH = 150;
constexpr int32_t PORTAL_HEIGHT = 153;

Portal::Portal(Vector2f position, Screen* level)
    : tex_{"resources/gfx/portal_small.png"}, level_{level}
{
    setup(&tex_, PORTAL_WIDTH, PORTAL_HEIGHT, position);
    gravity_scale_ = 0.0F;
    movable_ = false;
}

bool Portal::player_entered(Object& object_1, Object& object_2)
{
    Portal* portal = nullptr;
    portal = dynamic_cast<Portal*>(&object_1);
    if (!portal)
    {
        portal = dynamic_cast<Portal*>(&object_2);
    }

    if (!portal)
    {
        return false;
    }

    RuntimeCtx::app_->set_screen(portal->level_);

    return true;
}
