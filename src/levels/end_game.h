/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_END_GAME_H
#define SRC_LEVELS_END_GAME_H

#include <cstdint>

#include <rinvid/gui/label.h>
#include <rinvid/system/screen.h>

#include "src/pause_menu.h"

class EndGameScreen final : public rinvid::Screen
{
  public:
    enum class Ending
    {
        Continuation = 0,
        Boot
    };

    explicit EndGameScreen(Ending ending = Ending::Continuation);

    void create() override;
    void destroy() override;

  private:
    void update(double delta_time) override;
    void layout();
    void draw_message();
    void handle_pause_action(PauseAction action);

    Ending ending_;
    PauseMenu pause_menu_{};
    rinvid::gui::Label message_;
    rinvid::gui::Label secondary_message_;
    std::int32_t laid_out_width_{0};
    std::int32_t laid_out_height_{0};
};

#endif // SRC_LEVELS_END_GAME_H
