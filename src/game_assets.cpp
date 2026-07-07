/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/game_assets.h"

rinvid::Texture& GameAssets::player_texture()
{
    return player_texture_;
}

rinvid::Texture& GameAssets::box_texture()
{
    return box_texture_;
}

rinvid::Texture& GameAssets::portal_texture()
{
    return portal_texture_;
}

rinvid::Texture& GameAssets::text_box_texture()
{
    return text_box_texture_;
}
