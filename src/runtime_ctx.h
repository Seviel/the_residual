/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_RUNTIME_CTX_H
#define SRC_RUNTIME_CTX_H

#include <rinvid/core/camera.h>
#include <rinvid/system/application.h>

class ComBox;
class GameAssets;
class GameState;

using namespace rinvid;

class RuntimeCtx final
{
  public:
    RuntimeCtx()
    {
    }

    static void set_game_state(GameState* game_state);
    static GameState& game_state();
    static GameAssets& assets();
    static ComBox* com_box();

    static Camera camera_;
    static Application* app_;

  private:
    static GameState* game_state_;
};

#endif // SRC_RUNTIME_CTX_H
