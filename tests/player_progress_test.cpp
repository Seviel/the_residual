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
constexpr std::size_t SAVE_SIZE{TOKEN_SIZE * 2U};
constexpr std::uint64_t LEGACY_LEVEL_THREE_TOKEN{0xBA41F2549F047FC4ULL};

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

std::array<char, SAVE_SIZE> read_save(const std::filesystem::path& path)
{
    std::array<char, SAVE_SIZE> bytes{};
    std::ifstream input{path, std::ios::binary};
    input.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    return bytes;
}

void write_bytes(const std::filesystem::path& path, std::size_t byte_count)
{
    std::ofstream output{path, std::ios::binary | std::ios::trunc};
    const std::array<char, SAVE_SIZE + 1U> bytes{};
    output.write(bytes.data(), static_cast<std::streamsize>(byte_count));
}

void write_save(const std::filesystem::path& path,
                const std::array<char, SAVE_SIZE>& bytes)
{
    std::ofstream output{path, std::ios::binary | std::ios::trunc};
    output.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
}

void write_legacy_token(const std::filesystem::path& path, std::uint64_t token)
{
    std::array<char, TOKEN_SIZE> bytes{};
    for (std::size_t index{0U}; index < bytes.size(); ++index)
    {
        bytes[bytes.size() - index - 1U] = static_cast<char>(token & 0xFFU);
        token >>= 8U;
    }

    std::ofstream output{path, std::ios::binary | std::ios::trunc};
    output.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
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
        if (!expect(progress.farthest_level() == 0U, "A missing save must start at level 0") ||
            !expect(progress.last_visited_level() == 0U,
                    "A missing save must have no last visited level"))
        {
            return 1;
        }

        progress.visit(0U);
        progress.visit(PlayerProgress::LEVEL_COUNT + 1U);
        if (!expect(progress.farthest_level() == 0U, "Invalid levels must be ignored") ||
            !expect(progress.last_visited_level() == 0U,
                    "Invalid levels must not become the last visited level"))
        {
            return 1;
        }

        progress.visit(3U);
        if (!expect(progress.farthest_level() == 3U, "A visited level must be remembered") ||
            !expect(progress.last_visited_level() == 3U,
                    "A visited level must become the resume level") ||
            !expect(std::filesystem::file_size(save_path) == SAVE_SIZE,
                    "A save must contain exactly two opaque tokens"))
        {
            return 1;
        }

        const auto level_three_save{read_save(save_path)};
        std::filesystem::path temporary_save_path{save_path};
        temporary_save_path += ".tmp";
        std::filesystem::create_directory(temporary_save_path);
        progress.visit(3U);
        if (!expect(std::filesystem::is_directory(temporary_save_path),
                    "Visiting the current level must not rewrite a settled save"))
        {
            return 1;
        }
        std::filesystem::remove(temporary_save_path);

        progress.visit(2U);
        if (!expect(progress.farthest_level() == 3U, "Progress must never move backwards") ||
            !expect(progress.last_visited_level() == 2U,
                    "Visiting an earlier level must update the resume level") ||
            !expect(read_save(save_path) != level_three_save,
                    "Changing the resume level must update the save"))
        {
            return 1;
        }

        PlayerProgress reloaded{save_path};
        if (!expect(reloaded.farthest_level() == 3U,
                    "A valid save must load the farthest level") ||
            !expect(reloaded.last_visited_level() == 2U,
                    "A valid save must load the resume level"))
        {
            return 1;
        }

        reloaded.visit(PlayerProgress::LEVEL_COUNT);
        reloaded.visit(1U);
        PlayerProgress completed{save_path};
        if (!expect(completed.farthest_level() == PlayerProgress::LEVEL_COUNT,
                    "The farthest level must persist after starting over") ||
            !expect(completed.last_visited_level() == 1U,
                    "Starting over must move Continue back to level 1"))
        {
            return 1;
        }

        const std::filesystem::path blocked_directory{temporary_directory.path() / "blocked"};
        {
            std::ofstream blocking_file{blocked_directory};
        }
        const std::filesystem::path retry_save_path{blocked_directory / "progress.dat"};
        PlayerProgress retrying{retry_save_path};
        retrying.visit(2U);
        if (!expect(retrying.farthest_level() == 2U,
                    "A failed write must retain progress for the current session") ||
            !expect(retrying.last_visited_level() == 2U,
                    "A failed write must retain the resume level for the current session"))
        {
            return 1;
        }

        std::filesystem::remove(blocked_directory);
        retrying.visit(2U);
        PlayerProgress retried{retry_save_path};
        if (!expect(retried.farthest_level() == 2U,
                    "Visiting the same level must retry a previously failed save") ||
            !expect(retried.last_visited_level() == 2U,
                    "A retried save must retain the resume level"))
        {
            return 1;
        }

        write_legacy_token(save_path, LEGACY_LEVEL_THREE_TOKEN);
        PlayerProgress legacy{save_path};
        if (!expect(legacy.farthest_level() == 3U,
                    "A legacy token must load its farthest level") ||
            !expect(legacy.last_visited_level() == 3U,
                    "A legacy token must use its level as the resume level"))
        {
            return 1;
        }

        legacy.visit(3U);
        PlayerProgress migrated{save_path};
        if (!expect(std::filesystem::file_size(save_path) == SAVE_SIZE,
                    "The next visit must migrate a legacy save") ||
            !expect(migrated.farthest_level() == 3U,
                    "Migration must preserve the farthest level") ||
            !expect(migrated.last_visited_level() == 3U,
                    "Migration must preserve the resume level"))
        {
            return 1;
        }

        write_bytes(save_path, TOKEN_SIZE);
        PlayerProgress unknown_token{save_path};
        if (!expect(unknown_token.farthest_level() == 0U,
                    "An unknown legacy token must be treated as no save") ||
            !expect(unknown_token.last_visited_level() == 0U,
                    "An unknown legacy token must not supply a resume level"))
        {
            return 1;
        }

        write_bytes(save_path, SAVE_SIZE);
        PlayerProgress unknown_save{save_path};
        if (!expect(unknown_save.farthest_level() == 0U,
                    "Unknown current-format tokens must be treated as no save") ||
            !expect(unknown_save.last_visited_level() == 0U,
                    "Unknown current-format tokens must not supply a resume level"))
        {
            return 1;
        }

        write_bytes(save_path, SAVE_SIZE - 1U);
        PlayerProgress truncated{save_path};
        if (!expect(truncated.farthest_level() == 0U,
                    "A truncated save must be treated as no save") ||
            !expect(truncated.last_visited_level() == 0U,
                    "A truncated save must not supply a resume level"))
        {
            return 1;
        }

        write_bytes(save_path, SAVE_SIZE + 1U);
        PlayerProgress oversized{save_path};
        if (!expect(oversized.farthest_level() == 0U,
                    "An oversized save must be treated as no save") ||
            !expect(oversized.last_visited_level() == 0U,
                    "An oversized save must not supply a resume level"))
        {
            return 1;
        }

        const std::filesystem::path level_two_path{temporary_directory.path() /
                                                   "level_two.dat"};
        PlayerProgress level_two{level_two_path};
        level_two.visit(2U);
        auto inconsistent_save{read_save(level_two_path)};
        for (std::size_t index{TOKEN_SIZE}; index < SAVE_SIZE; ++index)
        {
            inconsistent_save[index] = level_three_save[index];
        }
        write_save(save_path, inconsistent_save);
        PlayerProgress inconsistent{save_path};
        if (!expect(inconsistent.farthest_level() == 0U,
                    "A resume level beyond the farthest level must invalidate the save") ||
            !expect(inconsistent.last_visited_level() == 0U,
                    "An inconsistent save must not supply a resume level"))
        {
            return 1;
        }

        inconsistent.visit(1U);
        PlayerProgress recovered{save_path};
        if (!expect(recovered.farthest_level() == 1U,
                    "Starting again must replace a damaged save") ||
            !expect(recovered.last_visited_level() == 1U,
                    "A recovered save must retain its resume level"))
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
