/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/levels.h"

#include <memory>

#include "src/levels/level_1.h"

std::unique_ptr<rinvid::Screen> Levels::level_1()
{
    return std::make_unique<Level_1>();
}
