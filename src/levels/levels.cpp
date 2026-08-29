/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/levels/levels.h"

#include <array>
#include <cstddef>
#include <memory>

#include "src/levels/end_game.h"
#include "src/levels/level_1.h"
#include "src/levels/level_10.h"
#include "src/levels/level_11.h"
#include "src/levels/level_12.h"
#include "src/levels/level_13.h"
#include "src/levels/level_14.h"
#include "src/levels/level_15.h"
#include "src/levels/level_16.h"
#include "src/levels/level_17.h"
#include "src/levels/level_18.h"
#include "src/levels/level_19.h"
#include "src/levels/level_2.h"
#include "src/levels/level_20.h"
#include "src/levels/level_21.h"
#include "src/levels/level_22.h"
#include "src/levels/level_23.h"
#include "src/levels/level_24.h"
#include "src/levels/level_3.h"
#include "src/levels/level_4.h"
#include "src/levels/level_5.h"
#include "src/levels/level_6.h"
#include "src/levels/level_7.h"
#include "src/levels/level_8.h"
#include "src/levels/level_9.h"

namespace
{

using LevelFactory = std::unique_ptr<rinvid::Screen> (*)();

const std::array<LevelFactory, Levels::LEVEL_COUNT> LEVEL_FACTORIES{
    Levels::level_1,  Levels::level_2,  Levels::level_3,  Levels::level_4,  Levels::level_5,
    Levels::level_6,  Levels::level_7,  Levels::level_8,  Levels::level_9,  Levels::level_10,
    Levels::level_11, Levels::level_12, Levels::level_13, Levels::level_14, Levels::level_15,
    Levels::level_16, Levels::level_17, Levels::level_18, Levels::level_19, Levels::level_20,
    Levels::level_21, Levels::level_22, Levels::level_23, Levels::level_24};

} // namespace

std::unique_ptr<rinvid::Screen> Levels::from_number(std::size_t level_number)
{
    if (level_number == 0U || level_number > LEVEL_FACTORIES.size())
    {
        return nullptr;
    }

    return LEVEL_FACTORIES[level_number - 1U]();
}

std::unique_ptr<rinvid::Screen> Levels::end_game()
{
    return std::make_unique<EndGameScreen>();
}

std::unique_ptr<rinvid::Screen> Levels::end_game_boot()
{
    return std::make_unique<EndGameScreen>(EndGameScreen::Ending::Boot);
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

std::unique_ptr<rinvid::Screen> Levels::level_6()
{
    return std::make_unique<Level_6>();
}

std::unique_ptr<rinvid::Screen> Levels::level_7()
{
    return std::make_unique<Level_7>();
}

std::unique_ptr<rinvid::Screen> Levels::level_8()
{
    return std::make_unique<Level_8>();
}

std::unique_ptr<rinvid::Screen> Levels::level_9()
{
    return std::make_unique<Level_9>();
}

std::unique_ptr<rinvid::Screen> Levels::level_10()
{
    return std::make_unique<Level_10>();
}

std::unique_ptr<rinvid::Screen> Levels::level_11()
{
    return std::make_unique<Level_11>();
}

std::unique_ptr<rinvid::Screen> Levels::level_12()
{
    return std::make_unique<Level_12>();
}

std::unique_ptr<rinvid::Screen> Levels::level_13()
{
    return std::make_unique<Level_13>();
}

std::unique_ptr<rinvid::Screen> Levels::level_14()
{
    return std::make_unique<Level_14>();
}

std::unique_ptr<rinvid::Screen> Levels::level_15()
{
    return std::make_unique<Level_15>();
}

std::unique_ptr<rinvid::Screen> Levels::level_16()
{
    return std::make_unique<Level_16>();
}

std::unique_ptr<rinvid::Screen> Levels::level_17()
{
    return std::make_unique<Level_17>();
}

std::unique_ptr<rinvid::Screen> Levels::level_18()
{
    return std::make_unique<Level_18>();
}

std::unique_ptr<rinvid::Screen> Levels::level_19()
{
    return std::make_unique<Level_19>();
}

std::unique_ptr<rinvid::Screen> Levels::level_20()
{
    return std::make_unique<Level_20>();
}

std::unique_ptr<rinvid::Screen> Levels::level_21()
{
    return std::make_unique<Level_21>();
}

std::unique_ptr<rinvid::Screen> Levels::level_22()
{
    return std::make_unique<Level_22>();
}

std::unique_ptr<rinvid::Screen> Levels::level_23()
{
    return std::make_unique<Level_23>();
}

std::unique_ptr<rinvid::Screen> Levels::level_24()
{
    return std::make_unique<Level_24>();
}
