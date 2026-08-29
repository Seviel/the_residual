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
    "Where am I?\nI don't remember lying down. I don't remember waking up. I don't remember "
    "anything.";
inline constexpr char LVL_1_OP_1[] =
    "You are awake.\nThis is enough for now.\nIt is crucial that you move forward.";

inline constexpr char LVL_2_PLAYER_1[] = "Someone is speaking to me.\nNot out loud.\nNot exactly.";
inline constexpr char LVL_2_OP_1[] = "Do not panic.\nI can guide you out.\nFollow the path.";

inline constexpr char LVL_3_PLAYER_1[] = "My name...\nWhy can't I remember my name?";
inline constexpr char LVL_3_OP_1[] =
    "Memory will come back to you in due time.\nDo not force it.\nJust keep moving.";

inline constexpr char LVL_4_PLAYER_1[] = "Why?\nWhat's there?";
inline constexpr char LVL_4_OP_1[] = "Not that way.";
inline constexpr char LVL_4_PLAYER_2[] = "What is this place?\nWhere am I going?";
inline constexpr char LVL_4_OP_2[] = "It's the wrong way.\nGo back.";

inline constexpr char LVL_5_OP_1[] = "The environment is unstable, but safe for now.";
inline constexpr char LVL_5_PLAYER_1[] =
    "This place feels unfinished.\nLike somebody built it from a dream.";
inline constexpr char LVL_5_OP_2[] = "Familiarity is not memory, ignore it!";
inline constexpr char LVL_5_PLAYER_2[] = "Some parts feel empty.\nOther parts feel familiar.";

inline constexpr char LVL_6_OP_1[] =
    "That was just auditory residue.\nIgnore it.\nDo not let it distract you, it's not real.";
inline constexpr char LVL_6_PLAYER_1[] =
    "I heard someone laugh.\nA girl. For a second I thought I knew that laugh.\nThen it was gone.";

inline constexpr char LVL_7_OP_1[] =
    "Your mind is playing tricks on you.\nIgnore it.\nFocus on the path.";
inline constexpr char LVL_7_PLAYER_1[] =
    "That laugh...\nI suddenly feel like I miss her.\nBut I can't remember who she is.";

inline constexpr char LVL_8_OP_1[] = "Do not follow scene fragments.\nThey are misleading.";
inline constexpr char LVL_8_PLAYER_1[] =
    "A train platform.\nIt was raining.\nShe was standing under the broken light.";
inline constexpr char LVL_8_OP_2[] = "Do not let anything distract you from moving forward.";
inline constexpr char LVL_8_PLAYER_2[] =
    "She was leaving.\nOr waiting for me.\nI can't remember which.";

inline constexpr char LVL_10_OP_1[] =
    "I do not know much about your past, but in this place, memories might "
    "not be real.\nDo not dwell on it.";
inline constexpr char LVL_10_PLAYER_1[] =
    "I remember a room full of people.\nEveryone was talking.\nI was just standing there, "
    "pretending to belong.";

inline constexpr char LVL_11_OP_1[] =
    "That may have been true, but it may be fabricated memory.\nYou will know once you get out of "
    "here.";
inline constexpr char LVL_11_PLAYER_1[] =
    "I remember my apartment. It was quiet. Too quiet.\nSometimes I would yell something to check "
    "if my voice still worked.";
inline constexpr char LVL_11_OP_2[] =
    "The exit is just several portals away.\nPlenty of time to regain your true memories after you "
    "get out.";
inline constexpr char LVL_11_PLAYER_2[] = "I think I was alone for a long time.";

inline constexpr char LVL_12_OP_1[] = "Dwelling on possibly false memories is dangerous.";
inline constexpr char LVL_12_PLAYER_1[] =
    "She noticed me.\nI remember that now.\nFinally I didn't feel invisible.";

inline constexpr char LVL_13_OP_1[] =
    "I know that word means something.\nI also know this is not the time to explain it.";
inline constexpr char LVL_13_PLAYER_1[] =
    "I remember signing something.\nA grey room.\nThe word Dreamscape on the wall.";

inline constexpr char LVL_14_OP_1[] =
    "Outcomes like this are rare.\nDreamscape was not built to harm people.\nRemember that when I "
    "guide you out.";
inline constexpr char LVL_14_PLAYER_1[] =
    "Someone asked if I understood the risk.\nI said yes.\nI don't think I did.";

inline constexpr char LVL_15_OP_1[] =
    "You are not the first person I tried to guide.\nBut you are the one still moving.";
inline constexpr char LVL_15_PLAYER_1[] =
    "You talk like you've done this before.\nLike I'm not the first.";

inline constexpr char LVL_16_OP_1[] =
    "I wish you had not remembered that yet.\nBut wishing is not part of my job.";
inline constexpr char LVL_16_PLAYER_1[] =
    "I remember a chair.\nCold metal against my hands.\nSomeone told me to relax.";

inline constexpr char LVL_17_OP_1[] =
    "People come here for many reasons.\nGrief. Loneliness. Regret.\nSometimes just to feel less "
    "alone.";
inline constexpr char LVL_17_PLAYER_1[] =
    "I came here willingly.\nThat feels true.\nBut I don't know what I wanted.";

inline constexpr char LVL_18_OP_1[] =
    "She exists in this place.\nThat is all I can safely tell you.";
inline constexpr char LVL_18_PLAYER_1[] =
    "That girl I remembered before...\nWho was she?\nIs she real?";

inline constexpr char LVL_19_OP_1[] =
    "The simulation is becoming unstable.\nI cannot slow it down anymore.\nYou need to hurry.";
inline constexpr char LVL_19_PLAYER_1[] =
    "The world is breaking apart.\nThe walls, the sky.\nWhat is happening?";

inline constexpr char LVL_20_OP_1[] =
    "You came to Dreamscape willingly.\nWe build simulated realities from memory, desire, and "
    "emotional need.";
inline constexpr char LVL_20_OP_2[] = "You paid us to create a world your mind could believe in.";

inline constexpr char LVL_21_OP_1[] =
    "You were lonely. More than lonely.\nYou wanted a life where someone will see you, understand "
    "you, and choose you.";

inline constexpr char LVL_22_OP_1[] =
    "The girl was part of that world.\nBuilt from everything you wanted and everything you feared "
    "losing.";

inline constexpr char LVL_22_OP_2[] = "When the experience was supposed to end, something failed.";

inline constexpr char LVL_23_OP_1[] =
    "Your memory fragmented, and the simulation began stitching together unstable worlds from what "
    "remained.";
inline constexpr char LVL_23_OP_2[] = "Dreamscape sent me in to guide you out.";

inline constexpr char LVL_24_OP_1[] =
    "I've opened the exit portal, it's on the left. It will lead you out of simulation and you "
    "will wake up.";

inline constexpr char LVL_24_OP_2[] = "Proceed to enter the portal.";

inline constexpr char LVL_24_OP_3[] = "Noooooooooooo!\nThis is the wrong portal!\nGo left!";

} // namespace GameText

#endif // SRC_GAME_TEXT_H
