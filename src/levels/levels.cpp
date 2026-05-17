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

#include "src/levels/gym.h"
#include "src/levels/level_1.h"
#include "src/levels/level_2.h"
#include "src/levels/level_3.h"
#include "src/levels/level_4.h"
#include "src/levels/level_5.h"

std::unique_ptr<rinvid::Screen> Levels::gym()
{
    return std::make_unique<GymScreen>();
}

std::unique_ptr<rinvid::Screen> Levels::level_1()
{
    return std::make_unique<Level_1>();
}

std::unique_ptr<rinvid::Screen> Levels::level_2()
{
    return std::make_unique<Level_2>();
}

std::unique_ptr<rinvid::Screen> Levels::level_3()
{
    return std::make_unique<Level_3>();
}

std::unique_ptr<rinvid::Screen> Levels::level_4()
{
    return std::make_unique<Level_4>();
}

std::unique_ptr<rinvid::Screen> Levels::level_5()
{
    return std::make_unique<Level_5>();
}
