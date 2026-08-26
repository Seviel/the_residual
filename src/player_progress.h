/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#ifndef SRC_PLAYER_PROGRESS_H
#define SRC_PLAYER_PROGRESS_H

#include <cstdint>
#include <filesystem>

class PlayerProgress final
{
  public:
    static constexpr std::uint32_t LEVEL_COUNT{24U};

    PlayerProgress();
    explicit PlayerProgress(std::filesystem::path save_path);

    std::uint32_t farthest_level() const noexcept;
    void reach(std::uint32_t level) noexcept;

  private:
    static std::filesystem::path default_save_path();

    void load() noexcept;
    bool save() const noexcept;

    std::filesystem::path save_path_;
    std::uint32_t farthest_level_{0U};
    bool save_pending_{false};
};

#endif // SRC_PLAYER_PROGRESS_H
