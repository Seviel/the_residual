/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "level_6.h"

#include <rinvid/core/render_context.h>
#include <rinvid/platformers/world.h>

#include "src/runtime_ctx.h"

namespace
{

constexpr float BACKGROUND_X{-100.0F};
constexpr float BACKGROUND_Y{0.0F};
constexpr float FAR_PARALLAX_X_FACTOR{0.18F};
constexpr float FAR_PARALLAX_Y_FACTOR{0.8F};

void draw_parallax_layer(Sprite& sprite, Vector2f camera_pos, float x_factor, float y_factor)
{
    sprite.set_position({BACKGROUND_X + camera_pos.x * (1.0F - x_factor),
                         BACKGROUND_Y + camera_pos.y * (1.0F - y_factor)});
    sprite.draw();
}

} // namespace

void Level_6::create_level()
{
    player_.setup(&player_texture_, 52, 100, Vector2f{1400.0F, 1000.0F}, Vector2f{0.0F, 0.0F});
    register_player(player_);

    RuntimeCtx::com_box()->set_text("");
    camera_.set_borders({-100.0F, 0.0F}, {900.0F, 700.0F});
}

void Level_6::update_level(double delta_time)
{
    player_.update(delta_time);
    for (auto* platform : platforms_)
    {
        platform->update(delta_time);
    }
    player_trig_1_.update(delta_time);
    op_trig_1_.update(delta_time);

    rinvid::World::collide(player_, platforms_, Player::separate_collision_boxes);
    rinvid::World::collide(player_, player_trig_1_, TextTrigger::reactivate_on_collision);
    rinvid::World::collide(player_, op_trig_1_, TextTrigger::reactivate_on_collision);
    rinvid::World::collide(player_, portal_, Portal::player_entered);

    auto camera_pos = player_.get_position();
    camera_pos.x -= get_render_context().get_width() / 2.0F;
    camera_pos.y -= get_render_context().get_height() / 2.0F;
    camera_.set_position(camera_pos);
    camera_.update();

    RuntimeCtx::com_box()->update(delta_time);
}

void Level_6::draw_level(double delta_time)
{
    draw_parallax_background();
    player_.draw(delta_time);
    portal_.draw(delta_time);
    RuntimeCtx::com_box()->draw();
}

void Level_6::draw_parallax_background()
{
    const auto camera_pos = camera_.get_pos();

    draw_parallax_layer(background_far_sprite_, camera_pos, FAR_PARALLAX_X_FACTOR,
                        FAR_PARALLAX_Y_FACTOR);
    background_foreground_sprite_.set_position({BACKGROUND_X, BACKGROUND_Y});
    background_foreground_sprite_.draw();
}

std::unique_ptr<rinvid::Screen> Level_6::restart_level() const
{
    return Levels::level_6();
}
