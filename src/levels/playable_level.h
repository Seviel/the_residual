/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_LEVELS_PLAYABLE_LEVEL_H
#define SRC_LEVELS_PLAYABLE_LEVEL_H

#include <memory>

#include <rinvid/system/screen.h>

#include "src/pause_menu.h"

class PlayableLevel : public rinvid::Screen
{
  public:
    PlayableLevel() = default;
    virtual ~PlayableLevel() = default;

    void create() final;
    void destroy() final;

  protected:
    virtual void create_level() = 0;
    virtual void destroy_level();
    virtual void update_level(double delta_time) = 0;
    virtual void draw_level(double delta_time) = 0;
    virtual std::unique_ptr<rinvid::Screen> restart_level() const = 0;

  private:
    void update(double delta_time) final;
    void handle_pause_action(PauseAction action);

    PauseMenu pause_menu_{};
};

#endif // SRC_LEVELS_PLAYABLE_LEVEL_H
