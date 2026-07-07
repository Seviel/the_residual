/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_GAME_STATE_H
#define SRC_GAME_STATE_H

#include "src/com_box.h"
#include "src/game_assets.h"

class GameState final
{
  public:
    GameState();

    GameAssets& assets();
    ComBox& com_box();

  private:
    GameAssets assets_;
    ComBox com_box_;
};

#endif // SRC_GAME_STATE_H
