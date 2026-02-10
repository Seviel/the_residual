/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_PORTAL_H
#define SRC_PORTAL_H

#include "core/include/sprite_object.h"

using namespace rinvid;

class Portal final : public rinvid::SpriteObject
{

  public:
    Portal(Vector2f position, Screen* level);

    static bool player_entered(Object& object_1, Object& object_2);

  private:
    Texture tex_;
    Screen* level_;
};

#endif // SRC_PORTAL_H
