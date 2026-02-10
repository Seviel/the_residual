/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/levels.h"

Level_1* Levels::level_1_{nullptr};

Level_1* Levels::level_1()
{
    if (level_1_ == nullptr)
    {
        level_1_ = new Level_1();
    }

    return level_1_;
}
