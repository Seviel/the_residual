/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_BOX_H
#define SRC_BOX_H

#include <rinvid/platformers/sprite_object.h>
#include <rinvid/util/vector2.h>

using namespace rinvid;

class Box : public SpriteObject
{

  public:
    Box(Vector2f position);
};

#endif // SRC_BOX_H
