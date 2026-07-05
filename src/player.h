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

#include <rinvid/platformers/sprite_object.h>

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

    void set_position(const Vector2f vector) override;
    void reset(Vector2f position) override;
    void move(const Vector2f move_vector) override;

    bool is_dead() const;
    bool has_fatal_fall_pending() const;
    void die();

    static bool separate_collision_boxes(Object& object_1, Object& object_2);
    static bool separate_moving_plat(Object& object_1, Object& object_2);

  private:
    static constexpr float FALL_DEATH_HEIGHT{450.0F};

    void update_internal(double delta_time);
    void update_collision_boxes(double delta_time);
    void sync_from_collision_boxes();
    void update_fall_death_state();
    void stop_motion();
    void play_death_animation();

    // Final velocity is internal_velocity_ + external_velocity_
    // Set for example by moving player with keys
    Vector2f internal_velocity_{};
    // Set by external forces, like by moving platform
    Vector2f external_velocity_{};
    bool facing_right_{true};
    bool is_riding_{false};
    bool dead_{false};
    bool is_tracking_fall_{false};
    bool fatal_fall_pending_{false};
    float fall_start_y_{0.0F};

    Object x_collision_box_{};
    Object y_collision_box_{};
};

#endif // SRC_PLAYER_H
