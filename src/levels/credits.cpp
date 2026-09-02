/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/credits.h"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <shellapi.h>
#endif

#include <rinvid/core/render_context.h>
#include <rinvid/system/application.h>
#include <rinvid/util/color.h>

#include "src/levels/main_menu.h"
#include "src/runtime_ctx.h"

namespace
{

constexpr const char* FONT_PATH{"resources/ttf/aquifer.ttf"};
constexpr const char* WEBSITE_URL{"https://www.dreamscape.dev/"};
constexpr const char* X_URL{"https://x.com/Seviel8"};
constexpr std::int32_t BUTTON_GAP{14};
constexpr std::int32_t OUTER_MARGIN{40};
constexpr float TITLE_TO_BUTTON_GAP{32.0F};

const rinvid::Color TITLE_COLOR{0x5DD3B6FF};

void open_url(const char* url)
{
#if defined(_WIN32)
    (void)ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);
#else
    const std::string command{"xdg-open \"" + std::string{url} + "\" >/dev/null 2>&1 &"};
    (void)std::system(command.c_str());
#endif
}

} // namespace

Credits::Credits()
    : title_{"Dreamscape Games",
             FONT_PATH,
             {0.0F, 0.0F},
             TITLE_COLOR,
             42,
             800.0F,
             rinvid::gui::LabelAlignment::Center}
{
}

void Credits::create()
{
    RuntimeCtx::camera_.set_borders({-2000.0F, -2000.0F}, {2000.0F, 2000.0F});
    RuntimeCtx::camera_.set_position({0.0F, 0.0F});
    RuntimeCtx::camera_.update();
}

void Credits::update(double delta_time)
{
    (void)delta_time;

    get_render_context().clear_screen(0.0F, 0.0F, 0.0F, 1.0F);
    background_sprite_.draw();

    layout();

    const bool website_activated{website_button_.update()};
    const bool x_activated{x_button_.update()};
    const bool back_activated{back_button_.update()};

    title_.draw();
    website_button_.draw();
    x_button_.draw();
    back_button_.draw();

    if (website_activated)
    {
        open_url(WEBSITE_URL);
    }
    else if (x_activated)
    {
        open_url(X_URL);
    }
    else if (back_activated)
    {
        this->get_application()->set_screen(std::make_unique<MainMenu>());
    }
}

void Credits::destroy()
{
}

void Credits::layout()
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
    const std::int32_t button_width{std::min(MenuButton::DEFAULT_WIDTH, available_width)};
    const float button_x{(static_cast<float>(screen_width) - static_cast<float>(button_width)) /
                         2.0F};
    const float title_y{std::max(52.0F, (static_cast<float>(screen_height) / 2.0F) - 110.0F)};
    float button_y{title_y + TITLE_TO_BUTTON_GAP};

    title_.set_bounds_width(static_cast<float>(screen_width));
    title_.set_position({0.0F, title_y});

    website_button_.set_bounds({{button_x, button_y}, button_width, MenuButton::DEFAULT_HEIGHT});
    button_y += MenuButton::DEFAULT_HEIGHT + BUTTON_GAP;
    x_button_.set_bounds({{button_x, button_y}, button_width, MenuButton::DEFAULT_HEIGHT});

    const float back_button_y{
        std::max(button_y + MenuButton::DEFAULT_HEIGHT + static_cast<float>(BUTTON_GAP),
                 static_cast<float>(screen_height - OUTER_MARGIN - MenuButton::DEFAULT_HEIGHT))};
    back_button_.set_bounds({{button_x, back_button_y}, button_width, MenuButton::DEFAULT_HEIGHT});
}
