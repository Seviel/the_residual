/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_GAME_ASSETS_H
#define SRC_GAME_ASSETS_H

#include <rinvid/core/texture.h>

class GameAssets final
{
  public:
    GameAssets() = default;

    rinvid::Texture& player_texture();
    rinvid::Texture& box_texture();
    rinvid::Texture& portal_texture();
    rinvid::Texture& text_box_texture();

  private:
    rinvid::Texture player_texture_{"resources/gfx/man_animated.png"};
    rinvid::Texture box_texture_{"resources/gfx/box.png"};
    rinvid::Texture portal_texture_{"resources/gfx/portal_small.png"};
    rinvid::Texture text_box_texture_{"resources/gfx/text_box.png"};
};

#endif // SRC_GAME_ASSETS_H
