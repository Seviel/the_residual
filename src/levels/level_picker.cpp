/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/level_picker.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <memory>

#include <rinvid/core/render_context.h>
#include <rinvid/system/application.h>

#include "src/levels/levels.h"
#include "src/levels/main_menu.h"
#include "src/runtime_ctx.h"

namespace
{

constexpr std::int32_t LEVEL_BUTTON_COLUMNS{6};
constexpr std::int32_t LEVEL_BUTTON_ROWS{4};
constexpr std::int32_t LEVEL_BUTTON_GAP{12};
constexpr std::int32_t LEVEL_BUTTON_WIDTH{92};
constexpr std::int32_t LEVEL_BUTTON_HEIGHT{48};
constexpr std::int32_t BACK_BUTTON_TOP_GAP{28};
constexpr std::int32_t OUTER_MARGIN{40};
constexpr std::size_t IMPLEMENTED_LEVEL_COUNT{24};

using LevelFactory = std::unique_ptr<rinvid::Screen> (*)();

const std::array<LevelFactory, IMPLEMENTED_LEVEL_COUNT> LEVEL_FACTORIES{
    Levels::level_1,  Levels::level_2,  Levels::level_3,  Levels::level_4,  Levels::level_5,
    Levels::level_6,  Levels::level_7,  Levels::level_8,  Levels::level_9,  Levels::level_10,
    Levels::level_11, Levels::level_12, Levels::level_13, Levels::level_14, Levels::level_15,
    Levels::level_16, Levels::level_17, Levels::level_18, Levels::level_19, Levels::level_20,
    Levels::level_21, Levels::level_22, Levels::level_23, Levels::level_24};

std::array<MenuButton, 24> make_level_buttons()
{
    return {MenuButton{"1"},  MenuButton{"2"},  MenuButton{"3"},  MenuButton{"4"},
            MenuButton{"5"},  MenuButton{"6"},  MenuButton{"7"},  MenuButton{"8"},
            MenuButton{"9"},  MenuButton{"10"}, MenuButton{"11"}, MenuButton{"12"},
            MenuButton{"13"}, MenuButton{"14"}, MenuButton{"15"}, MenuButton{"16"},
            MenuButton{"17"}, MenuButton{"18"}, MenuButton{"19"}, MenuButton{"20"},
            MenuButton{"21"}, MenuButton{"22"}, MenuButton{"23"}, MenuButton{"24"}};
}

} // namespace

LevelPicker::LevelPicker() : level_buttons_{make_level_buttons()}
{
}

void LevelPicker::create()
{
    RuntimeCtx::camera_.set_borders({-2000.0F, -2000.0F}, {2000.0F, 2000.0F});
    RuntimeCtx::camera_.set_position({0.0F, 0.0F});
    RuntimeCtx::camera_.update();

    // Development behavior: every implemented level is selectable. Later this should come from
    // the player's highest reached level.
    const std::size_t selectable_level_count{IMPLEMENTED_LEVEL_COUNT};
    for (std::size_t level_index{0}; level_index < level_buttons_.size(); ++level_index)
    {
        level_buttons_[level_index].set_enabled(level_index < selectable_level_count);
    }
}

void LevelPicker::update(double delta_time)
{
    (void)delta_time;

    get_render_context().clear_screen(0.0F, 0.0F, 0.0F, 1.0F);
    background_sprite_.draw();

    layout();

    for (std::size_t level_index{0}; level_index < level_buttons_.size(); ++level_index)
    {
        if (level_buttons_[level_index].update() && level_index < LEVEL_FACTORIES.size())
        {
            this->get_application()->set_screen(LEVEL_FACTORIES[level_index]());
        }
    }

    const bool back_activated{back_button_.update()};

    for (MenuButton& level_button : level_buttons_)
    {
        level_button.draw();
    }
    back_button_.draw();

    if (back_activated)
    {
        this->get_application()->set_screen(std::make_unique<MainMenu>());
    }
}

void LevelPicker::destroy()
{
}

void LevelPicker::layout()
{
    const std::int32_t screen_width{get_render_context().get_width()};
    const std::int32_t screen_height{get_render_context().get_height()};
    if (screen_width == laid_out_width_ && screen_height == laid_out_height_)
    {
        return;
    }

    laid_out_width_ = screen_width;
    laid_out_height_ = screen_height;

    const std::int32_t available_width{std::max(0, screen_width - OUTER_MARGIN)};
    const std::int32_t grid_gap_width{(LEVEL_BUTTON_COLUMNS - 1) * LEVEL_BUTTON_GAP};
    const std::int32_t fitted_button_width{(available_width - grid_gap_width) /
                                           LEVEL_BUTTON_COLUMNS};
    const std::int32_t button_width{std::min(LEVEL_BUTTON_WIDTH, std::max(0, fitted_button_width))};
    const std::int32_t grid_width{(LEVEL_BUTTON_COLUMNS * button_width) + grid_gap_width};
    const std::int32_t grid_height{(LEVEL_BUTTON_ROWS * LEVEL_BUTTON_HEIGHT) +
                                   ((LEVEL_BUTTON_ROWS - 1) * LEVEL_BUTTON_GAP)};
    const std::int32_t total_height{grid_height + BACK_BUTTON_TOP_GAP + MenuButton::DEFAULT_HEIGHT};

    const float grid_x{(static_cast<float>(screen_width) - static_cast<float>(grid_width)) / 2.0F};
    const float grid_y{(static_cast<float>(screen_height) - static_cast<float>(total_height)) /
                       2.0F};

    for (std::int32_t index{0}; index < static_cast<std::int32_t>(level_buttons_.size()); ++index)
    {
        const std::int32_t row{index / LEVEL_BUTTON_COLUMNS};
        const std::int32_t column{index % LEVEL_BUTTON_COLUMNS};
        const std::int32_t button_step_x{button_width + LEVEL_BUTTON_GAP};
        const std::int32_t button_step_y{LEVEL_BUTTON_HEIGHT + LEVEL_BUTTON_GAP};
        const float button_x{grid_x + static_cast<float>(column * button_step_x)};
        const float button_y{grid_y + static_cast<float>(row * button_step_y)};

        level_buttons_[static_cast<std::size_t>(index)].set_bounds(
            {{button_x, button_y}, button_width, LEVEL_BUTTON_HEIGHT});
    }

    const std::int32_t back_button_width{std::min(MenuButton::DEFAULT_WIDTH, available_width)};
    const float back_button_x{
        (static_cast<float>(screen_width) - static_cast<float>(back_button_width)) / 2.0F};
    const float back_button_y{grid_y + static_cast<float>(grid_height + BACK_BUTTON_TOP_GAP)};
    back_button_.set_bounds(
        {{back_button_x, back_button_y}, back_button_width, MenuButton::DEFAULT_HEIGHT});
}
