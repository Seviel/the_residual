/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/com_box.h"
#include "src/runtime_ctx.h"

using namespace rinvid;

constexpr int32_t BOX_WIDTH = 724;
constexpr int32_t BOX_HEIGHT = 124;

constexpr float BOX_X_OFFSET = 38.0F;
constexpr float BOX_Y_OFFSET = 20.0F;

constexpr float TEXT_X_OFFSET = 60.0F;
constexpr float TEXT_Y_OFFSET = 60.0F;

ComBox::ComBox()
    : tex_{"resources/gfx/text_box.png"}, text_{"Well hello there!", "resources/ttf/aquifer.ttf",
                                                Vector2f{0.0F, 0.0F}, Color{0x5DD3B6FF}, 24},
      content_{}
{
    setup(&tex_, BOX_WIDTH, BOX_HEIGHT, Vector2f{0.0F, 0.0F});
}

void ComBox::update(double delta_time)
{
    (void)delta_time;

    Vector2f camera_pos = RuntimeCtx::camera_.get_pos();
    this->set_position({camera_pos.x + BOX_X_OFFSET, camera_pos.y + BOX_Y_OFFSET});
    text_.set_position({camera_pos.x + TEXT_X_OFFSET, camera_pos.y + TEXT_Y_OFFSET});
}

void ComBox::draw()
{

    Sprite::draw();
    text_.draw();
}

void ComBox::set_text(std::string text)
{
    content_ = text;
    text_.set_text(content_);
}
