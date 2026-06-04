/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_GAME_TEXT_H
#define SRC_GAME_TEXT_H

namespace GameText
{

inline constexpr char LVL_1_PLAYER_1[] =
    "Where am I? I don't remember lying down. I don't remember waking up. I don't remember "
    "anything.";
inline constexpr char LVL_1_OP_1[] =
    "You are awake. This is enough for now. It is crucial that you move forward.";

inline constexpr char LVL_2_PLAYER_1[] = "Someone is speaking to me.\nNot out loud.\nNot exactly.";
inline constexpr char LVL_2_OP_1[] = "Do not panic.\nI can guide you out.\nFollow the path.";

inline constexpr char LVL_3_PLAYER_1[] = "My name...\nWhy can't I remember my name?";
inline constexpr char LVL_3_OP_1[] =
    "Memory will come back to you in due time.\nDo not force it.\nJust keep moving.";

inline constexpr char LVL_4_OP_1[] = "Level 4";
inline constexpr char LVL_5_OP_1[] = "Level 5";

inline constexpr char GYM_NICE_JUMP[] = "Nice jump!";
inline constexpr char GYM_SINGLE_TRIGGER[] = "Single trigger";

} // namespace GameText

#endif // SRC_GAME_TEXT_H
