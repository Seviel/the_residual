/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "main_menu.h"

#include <algorithm>
#include <memory>

#include <rinvid/core/render_context.h>
#include <rinvid/system/application.h>

#include "src/levels/gym.h"
#include "src/levels/level_picker.h"
#include "src/runtime_ctx.h"

namespace
{

constexpr std::int32_t BUTTON_GAP{14};
constexpr std::int32_t MENU_BUTTON_COUNT{5};

} // namespace

void MainMenu::create()
{
    RuntimeCtx::camera_.set_borders({-2000.0F, -2000.0F}, {2000.0F, 2000.0F});
    RuntimeCtx::camera_.set_position({0.0F, 0.0F});
    RuntimeCtx::camera_.update();

    continue_button_.set_enabled(false);
    credits_button_.set_enabled(false);
}

void MainMenu::update(double delta_time)
{
    (void)delta_time;

    get_render_context().clear_screen(0.0F, 0.0F, 0.0F, 1.0F);
    background_sprite_.draw();

    layout();

    const bool play_activated{play_button_.update()};
    continue_button_.update();
    const bool pick_level_activated{pick_level_button_.update()};
    credits_button_.update();
    const bool exit_activated{exit_button_.update()};

    continue_button_.draw();
    play_button_.draw();
    pick_level_button_.draw();
    credits_button_.draw();
    exit_button_.draw();

    if (play_activated)
    {
        this->get_application()->set_screen(std::make_unique<GymScreen>());
    }
    else if (pick_level_activated)
    {
        this->get_application()->set_screen(std::make_unique<LevelPicker>());
    }
    else if (exit_activated)
    {
        this->get_application()->exit();
    }
}

void MainMenu::destroy()
{
}

void MainMenu::layout()
{
    const std::int32_t screen_width{get_render_context().get_width()};
    const std::int32_t screen_height{get_render_context().get_height()};
    if (screen_width == laid_out_width_ && screen_height == laid_out_height_)
    {
        return;
    }

    laid_out_width_ = screen_width;
    laid_out_height_ = screen_height;

    const std::int32_t available_width{std::max(0, screen_width - 40)};
    const std::int32_t button_width{std::min(MenuButton::DEFAULT_WIDTH, available_width)};
    const std::int32_t total_height{(MENU_BUTTON_COUNT * MenuButton::DEFAULT_HEIGHT) +
                                    ((MENU_BUTTON_COUNT - 1) * BUTTON_GAP)};
    const float button_x{(static_cast<float>(screen_width) - static_cast<float>(button_width)) /
                         2.0F};
    float button_y{(static_cast<float>(screen_height) - static_cast<float>(total_height)) / 2.0F};

    continue_button_.set_bounds({{button_x, button_y}, button_width, MenuButton::DEFAULT_HEIGHT});
    button_y += MenuButton::DEFAULT_HEIGHT + BUTTON_GAP;
    play_button_.set_bounds({{button_x, button_y}, button_width, MenuButton::DEFAULT_HEIGHT});
    button_y += MenuButton::DEFAULT_HEIGHT + BUTTON_GAP;
    pick_level_button_.set_bounds({{button_x, button_y}, button_width, MenuButton::DEFAULT_HEIGHT});
    button_y += MenuButton::DEFAULT_HEIGHT + BUTTON_GAP;
    credits_button_.set_bounds({{button_x, button_y}, button_width, MenuButton::DEFAULT_HEIGHT});
    button_y += MenuButton::DEFAULT_HEIGHT + BUTTON_GAP;
    exit_button_.set_bounds({{button_x, button_y}, button_width, MenuButton::DEFAULT_HEIGHT});
}
