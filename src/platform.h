/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_PLATFORM_H
#define SRC_PLATFORM_H

#include <cstdint>

#include <rinvid/core/rectangle_shape.h>
#include <rinvid/platformers/object.h>
#include <rinvid/util/vector2.h>

using namespace rinvid;

class Platform : public rinvid::Object
{

  public:
    /**************************************************************************************************
     * @brief Default constructor.
     *
     *************************************************************************************************/

    Platform(Vector2f position, float width, float height, std::uint8_t movable = NOT);

    void update(double delta_time) override;
    void draw();

  private:
    rinvid::RectangleShape rect;
};

#endif // SRC_PLATFORM_H
