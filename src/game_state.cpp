/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/game_state.h"

GameState::GameState() : assets_{}, com_box_{assets_.text_box_texture()}
{
}

GameAssets& GameState::assets()
{
    return assets_;
}

ComBox& GameState::com_box()
{
    return com_box_;
}
