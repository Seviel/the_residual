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

    static std::unique_ptr<rinvid::Screen> gym();
    static std::unique_ptr<rinvid::Screen> level_1();
    static std::unique_ptr<rinvid::Screen> level_2();
    static std::unique_ptr<rinvid::Screen> level_3();
    static std::unique_ptr<rinvid::Screen> level_4();
    static std::unique_ptr<rinvid::Screen> level_5();
    static std::unique_ptr<rinvid::Screen> level_6();
    static std::unique_ptr<rinvid::Screen> level_7();
    static std::unique_ptr<rinvid::Screen> level_8();
    static std::unique_ptr<rinvid::Screen> level_9();
    static std::unique_ptr<rinvid::Screen> level_10();
    static std::unique_ptr<rinvid::Screen> level_11();
    static std::unique_ptr<rinvid::Screen> level_12();
    static std::unique_ptr<rinvid::Screen> level_13();
    static std::unique_ptr<rinvid::Screen> level_14();
    static std::unique_ptr<rinvid::Screen> level_15();
    static std::unique_ptr<rinvid::Screen> level_16();
    static std::unique_ptr<rinvid::Screen> level_17();
    static std::unique_ptr<rinvid::Screen> level_18();
    static std::unique_ptr<rinvid::Screen> level_19();
    static std::unique_ptr<rinvid::Screen> level_20();
    static std::unique_ptr<rinvid::Screen> level_21();
    static std::unique_ptr<rinvid::Screen> level_22();
    static std::unique_ptr<rinvid::Screen> level_23();
    static std::unique_ptr<rinvid::Screen> level_24();
};

#endif // SRC_LEVELS_LEVELS_H
