/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_TEXT_TRIGGER_H
#define SRC_TEXT_TRIGGER_H

#include <string>

#include "core/include/object.h"
#include "util/include/rect.h"
#include "util/include/vector2.h"

using namespace rinvid;

class TextTrigger : public rinvid::Object
{

  public:
    TextTrigger(std::string text, Vector2f position, std::int32_t width = 50,
                std::int32_t height = 200);

    void update(double delta_time) override;

    // Activates text only the first time it's callled.
    void activate();

    // Activates text every time it's called.
    void reactivate();

    static bool activate_on_collision(Object& object_1, Object& object_2);
    static bool reactivate_on_collision(Object& object_1, Object& object_2);

  private:
    std::string text_;
    rinvid::Rect rect;
};

#endif // SRC_TEXT_TRIGGER_H
