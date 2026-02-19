/**********************************************************************
 * Copyright (c) 2025 - 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H

#include "core/include/sprite_object.h"

using namespace rinvid;

class Player : public rinvid::SpriteObject
{

  public:
    /**************************************************************************************************
     * @brief Default constructor.
     *
     *************************************************************************************************/

    Player();

    void update(double delta_time) override;

    static bool separate_moving_plat(Object& object_1, Object& object_2);

  private:
    void update_internal(double delta_time);
    // Final velocity is internal_velocity_ + external_velocity_
    // Set for example by moving player with keys
    Vector2f internal_velocity_{};
    // Set by external forces, like by moving platform
    Vector2f external_velocity_{};
    bool facing_right_{true};
    bool is_riding_{false};
};

#endif // SRC_PLAYER_H
