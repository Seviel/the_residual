/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include <array>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>

#include "src/player_progress.h"

namespace
{

constexpr std::size_t TOKEN_SIZE{8U};

class TemporaryDirectory final
{
  public:
    TemporaryDirectory()
        : path_{std::filesystem::temp_directory_path() /
                ("the_residual_progress_test_" +
                 std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))}
    {
    }

    ~TemporaryDirectory()
    {
        std::error_code error;
        std::filesystem::remove_all(path_, error);
    }

    const std::filesystem::path& path() const
    {
        return path_;
    }

  private:
    std::filesystem::path path_;
};

bool expect(bool condition, const char* message)
{
    if (!condition)
    {
        std::cerr << message << '\n';
    }
    return condition;
}

std::array<char, TOKEN_SIZE> read_token(const std::filesystem::path& path)
{
    std::array<char, TOKEN_SIZE> bytes{};
    std::ifstream input{path, std::ios::binary};
    input.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    return bytes;
}

void write_bytes(const std::filesystem::path& path, std::size_t byte_count)
{
    std::ofstream output{path, std::ios::binary | std::ios::trunc};
    const std::array<char, TOKEN_SIZE + 1U> bytes{};
    output.write(bytes.data(), static_cast<std::streamsize>(byte_count));
}

} // namespace

int main()
{
    try
    {
        TemporaryDirectory temporary_directory;
        const std::filesystem::path save_path{temporary_directory.path() / "nested" /
                                              "progress.dat"};

        PlayerProgress progress{save_path};
        if (!expect(progress.farthest_level() == 0U, "A missing save must start at level 0"))
        {
            return 1;
        }

        progress.reach(0U);
        progress.reach(PlayerProgress::LEVEL_COUNT + 1U);
        if (!expect(progress.farthest_level() == 0U, "Invalid levels must be ignored"))
        {
            return 1;
        }

        progress.reach(3U);
        if (!expect(progress.farthest_level() == 3U, "A reached level must be remembered") ||
            !expect(std::filesystem::file_size(save_path) == TOKEN_SIZE,
                    "A save must contain exactly one opaque token"))
        {
            return 1;
        }

        const auto level_three_token{read_token(save_path)};
        progress.reach(2U);
        if (!expect(progress.farthest_level() == 3U, "Progress must never move backwards") ||
            !expect(read_token(save_path) == level_three_token,
                    "Replaying an earlier level must not rewrite the save"))
        {
            return 1;
        }

        PlayerProgress reloaded{save_path};
        if (!expect(reloaded.farthest_level() == 3U, "A valid token must load its level"))
        {
            return 1;
        }

        reloaded.reach(PlayerProgress::LEVEL_COUNT);
        PlayerProgress completed{save_path};
        if (!expect(completed.farthest_level() == PlayerProgress::LEVEL_COUNT,
                    "The last level must persist"))
        {
            return 1;
        }

        const std::filesystem::path blocked_directory{temporary_directory.path() / "blocked"};
        {
            std::ofstream blocking_file{blocked_directory};
        }
        const std::filesystem::path retry_save_path{blocked_directory / "progress.dat"};
        PlayerProgress retrying{retry_save_path};
        retrying.reach(2U);
        if (!expect(retrying.farthest_level() == 2U,
                    "A failed write must retain progress for the current session"))
        {
            return 1;
        }

        std::filesystem::remove(blocked_directory);
        retrying.reach(2U);
        PlayerProgress retried{retry_save_path};
        if (!expect(retried.farthest_level() == 2U,
                    "Reaching the same level must retry a previously failed save"))
        {
            return 1;
        }

        write_bytes(save_path, TOKEN_SIZE);
        PlayerProgress unknown_token{save_path};
        if (!expect(unknown_token.farthest_level() == 0U,
                    "An unknown token must be treated as no save"))
        {
            return 1;
        }

        write_bytes(save_path, TOKEN_SIZE - 1U);
        PlayerProgress truncated{save_path};
        if (!expect(truncated.farthest_level() == 0U,
                    "A truncated save must be treated as no save"))
        {
            return 1;
        }

        write_bytes(save_path, TOKEN_SIZE + 1U);
        PlayerProgress oversized{save_path};
        if (!expect(oversized.farthest_level() == 0U,
                    "An oversized save must be treated as no save"))
        {
            return 1;
        }

        oversized.reach(1U);
        PlayerProgress recovered{save_path};
        if (!expect(recovered.farthest_level() == 1U,
                    "Starting again must replace a damaged save"))
        {
            return 1;
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
