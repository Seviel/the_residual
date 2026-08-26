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

constexpr std::int32_t LEVEL_BUTTON_MAX_COLUMNS{6};
constexpr std::int32_t LEVEL_BUTTON_GAP{12};
constexpr std::int32_t LEVEL_BUTTON_WIDTH{92};
constexpr std::int32_t LEVEL_BUTTON_HEIGHT{48};
constexpr std::uint32_t LEVEL_BUTTON_STATE_COUNT{4U};
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

} // namespace

LevelPicker::LevelPicker()
{
    for (std::size_t level_index{0}; level_index < level_buttons_.size(); ++level_index)
    {
        const float atlas_y{static_cast<float>(level_index * LEVEL_BUTTON_HEIGHT)};
        level_buttons_[level_index].setup_from_atlas(
            &level_button_atlas_texture_, LEVEL_BUTTON_WIDTH, LEVEL_BUTTON_HEIGHT,
            Vector2f{0.0F, 0.0F}, LEVEL_BUTTON_STATE_COUNT, Vector2f{0.0F, atlas_y});
    }
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
        level_buttons_[level_index].update();
        if (level_buttons_[level_index].was_activated() && level_index < LEVEL_FACTORIES.size())
        {
            this->get_application()->set_screen(LEVEL_FACTORIES[level_index]());
        }
    }

    const bool back_activated{back_button_.update()};

    for (rinvid::gui::Button& level_button : level_buttons_)
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
    const std::int32_t available_grid_height{
        std::max(0, screen_height - OUTER_MARGIN - BACK_BUTTON_TOP_GAP -
                        MenuButton::DEFAULT_HEIGHT)};
    const std::int32_t fitted_column_count{
        (available_width + LEVEL_BUTTON_GAP) / (LEVEL_BUTTON_WIDTH + LEVEL_BUTTON_GAP)};
    const std::int32_t button_count{static_cast<std::int32_t>(level_buttons_.size())};
    const std::int32_t fitted_row_count{
        std::max(1, (available_grid_height + LEVEL_BUTTON_GAP) /
                        (LEVEL_BUTTON_HEIGHT + LEVEL_BUTTON_GAP))};
    const std::int32_t minimum_column_count{
        (button_count + fitted_row_count - 1) / fitted_row_count};
    const std::int32_t column_count{std::min(
        LEVEL_BUTTON_MAX_COLUMNS,
        std::max(1, std::max(fitted_column_count, minimum_column_count)))};
    const std::int32_t row_count{(button_count + column_count - 1) / column_count};
    const std::int32_t grid_gap_width{(column_count - 1) * LEVEL_BUTTON_GAP};
    const std::int32_t grid_width{(column_count * LEVEL_BUTTON_WIDTH) + grid_gap_width};
    const std::int32_t grid_height{(row_count * LEVEL_BUTTON_HEIGHT) +
                                   ((row_count - 1) * LEVEL_BUTTON_GAP)};
    const std::int32_t total_height{grid_height + BACK_BUTTON_TOP_GAP + MenuButton::DEFAULT_HEIGHT};

    const float grid_x{(static_cast<float>(screen_width) - static_cast<float>(grid_width)) / 2.0F};
    const float grid_y{(static_cast<float>(screen_height) - static_cast<float>(total_height)) /
                       2.0F};

    for (std::int32_t index{0}; index < static_cast<std::int32_t>(level_buttons_.size()); ++index)
    {
        const std::int32_t row{index / column_count};
        const std::int32_t column{index % column_count};
        const std::int32_t button_step_x{LEVEL_BUTTON_WIDTH + LEVEL_BUTTON_GAP};
        const std::int32_t button_step_y{LEVEL_BUTTON_HEIGHT + LEVEL_BUTTON_GAP};
        const float button_x{grid_x + static_cast<float>(column * button_step_x)};
        const float button_y{grid_y + static_cast<float>(row * button_step_y)};

        level_buttons_[static_cast<std::size_t>(index)].set_position({button_x, button_y});
    }

    const std::int32_t back_button_width{std::min(MenuButton::DEFAULT_WIDTH, available_width)};
    const float back_button_x{
        (static_cast<float>(screen_width) - static_cast<float>(back_button_width)) / 2.0F};
    const float back_button_y{grid_y + static_cast<float>(grid_height + BACK_BUTTON_TOP_GAP)};
    back_button_.set_bounds(
        {{back_button_x, back_button_y}, back_button_width, MenuButton::DEFAULT_HEIGHT});
}
