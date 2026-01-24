/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/text_trigger.h"
#include "src/runtime_ctx.h"

using namespace rinvid;

TextTrigger::TextTrigger(std::string text, Vector2f position, std::int32_t width,
                         std::int32_t height)
    : text_{text}, rect{position, width, height}
{
    reset(position);
    resize(width, height);
    set_movable(false);
    set_gravity_scale(0.0F);
}

void TextTrigger::update(double delta_time)
{
    Object::update(delta_time);
}

void TextTrigger::activate()
{
    if (active_)
    {
        RuntimeCtx::com_box()->set_text(text_);
        kill();
    }
}

void TextTrigger::reactivate()
{
    if (active_)
    {
        RuntimeCtx::com_box()->set_text(text_);
    }
}
