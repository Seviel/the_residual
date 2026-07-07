/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "runtime_ctx.h"

#include <stdexcept>

#include "src/game_state.h"

Camera RuntimeCtx::camera_{};
Application* RuntimeCtx::app_{nullptr};
GameState* RuntimeCtx::game_state_{nullptr};

void RuntimeCtx::set_game_state(GameState* game_state)
{
    game_state_ = game_state;
}

GameState& RuntimeCtx::game_state()
{
    if (game_state_ == nullptr)
    {
        throw std::logic_error{"RuntimeCtx: game state is not initialized"};
    }

    return *game_state_;
}

GameAssets& RuntimeCtx::assets()
{
    return game_state().assets();
}

ComBox* RuntimeCtx::com_box()
{
    return &game_state().com_box();
}
