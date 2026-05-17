/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_LEVELS_H
#define SRC_LEVELS_LEVELS_H

#include <memory>

#include <rinvid/system/screen.h>

using namespace rinvid;

class Levels final
{
  public:
    Levels()
    {
    }

    static std::unique_ptr<rinvid::Screen> level_1();
};

#endif // SRC_LEVELS_LEVELS_H
