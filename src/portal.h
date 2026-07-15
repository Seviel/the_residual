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

#include <memory>

#include <rinvid/platformers/sprite_object.h>
#include <rinvid/system/screen.h>

using namespace rinvid;

class Portal final : public rinvid::SpriteObject
{

  public:
    using LevelFactory = std::unique_ptr<rinvid::Screen> (*)();

    Portal(Vector2f position, LevelFactory level_factory);

    Rect bounding_rect() override;

    static bool player_entered(Object& object_1, Object& object_2);

  private:
    LevelFactory level_factory_;
};

#endif // SRC_PORTAL_H
