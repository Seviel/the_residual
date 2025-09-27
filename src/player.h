/**********************************************************************
 * Copyright (c) 2025, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H

#include "core/include/sprite.h"

class Player : public rinvid::Sprite
{

  public:
    /**************************************************************************************************
     * @brief Default constructor.
     *
     *************************************************************************************************/

    Player();

    void update(double delta_time) override;

  private:
    void update_internal(double delta_time);
    bool facing_right_{true};
};

#endif // SRC_PLAYER_H
