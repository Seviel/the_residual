/**********************************************************************
 * Copyright (c) 2026, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include "src/player_progress.h"

#include <array>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <system_error>
#include <utility>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

namespace
{

constexpr std::size_t TOKEN_SIZE{8U};
constexpr std::size_t LEGACY_SERIALIZED_SIZE{TOKEN_SIZE};
constexpr std::size_t SERIALIZED_SIZE{TOKEN_SIZE * 2U};
constexpr std::array<std::uint64_t, PlayerProgress::LEVEL_COUNT> FARTHEST_LEVEL_TOKENS{
    0xDB0BC1B23EFFEE58ULL, 0xAB155E118124C69EULL, 0xBA41F2549F047FC4ULL,
    0x0BFEA0C779E4146FULL, 0xA0446638F5F06273ULL, 0xFB5EBB9B30B4C948ULL,
    0x538EE11C9386E481ULL, 0x4494F78212FC7982ULL, 0xD5F78DD5BDF558E6ULL,
    0xD4F52DB3840DF62BULL, 0x682880822B0870F2ULL, 0x2F856D4521DE2CC0ULL,
    0x371CAE81D234ABFEULL, 0xF6212EC2AE56D78AULL, 0x8C76C9B4A9258A3CULL,
    0xB8CBED635EAA840CULL, 0x07F16171511ED1F3ULL, 0x63FB952BD120EACCULL,
    0x283EDAB430FD11E3ULL, 0x36AB355EFEB773C9ULL, 0x47BCADC2DD03A7B6ULL,
    0xF407ADAF0C8B327CULL, 0x582B8525430911C8ULL, 0xD24FF68950E5E86DULL};

constexpr std::array<std::uint64_t, PlayerProgress::LEVEL_COUNT> LAST_VISITED_TOKENS{
    0x41BEA32CCF049B75ULL, 0xE96C15A2B113D4F8ULL, 0x72F54CA903DE681BULL,
    0x193B8FD4E62C507AULL, 0xC8A764215DB9F30EULL, 0x56D20BE8A17C43F9ULL,
    0xAD03E65974B821CFULL, 0x2E9F714BC503DA86ULL, 0xF1530C7EA9426BD4ULL,
    0x847AB52FD019E36CULL, 0x3C61E8D590AF247BULL, 0x9D2843F6BE70C15AULL,
    0x678EF1094AD352BCULL, 0xB42C7D83F56019AEULL, 0x0DA935E271CB84F6ULL,
    0xEA7419C65B2F308DULL, 0x258CF3A7D6104E9BULL, 0x7B10D694CE83A52FULL,
    0xD6934B2A18F7C05EULL, 0x4FC0279E63AD815BULL, 0xA13DE80B75264FC9ULL,
    0x35B9F4610C8E72DAULL, 0x8E052AC79D31B46FULL, 0xCA6F17D348E2905BULL};

constexpr bool token_table_is_valid(
    const std::array<std::uint64_t, PlayerProgress::LEVEL_COUNT>& tokens)
{
    for (std::size_t index{0U}; index < tokens.size(); ++index)
    {
        if (tokens[index] == 0U)
        {
            return false;
        }

        for (std::size_t other_index{index + 1U}; other_index < tokens.size();
             ++other_index)
        {
            if (tokens[index] == tokens[other_index])
            {
                return false;
            }
        }
    }

    return true;
}

constexpr bool token_tables_are_disjoint()
{
    for (const std::uint64_t farthest_level_token : FARTHEST_LEVEL_TOKENS)
    {
        for (const std::uint64_t last_visited_token : LAST_VISITED_TOKENS)
        {
            if (farthest_level_token == last_visited_token)
            {
                return false;
            }
        }
    }
    return true;
}

static_assert(token_table_is_valid(FARTHEST_LEVEL_TOKENS),
              "Every farthest-level token must be unique and nonzero");
static_assert(token_table_is_valid(LAST_VISITED_TOKENS),
              "Every last-visited token must be unique and nonzero");
static_assert(token_tables_are_disjoint(), "Save token roles must not overlap");

std::uint64_t deserialize_token(const std::array<std::uint8_t, SERIALIZED_SIZE + 1U>& bytes,
                                const std::size_t offset)
{
    std::uint64_t token{0U};
    for (std::size_t index{offset}; index < offset + TOKEN_SIZE; ++index)
    {
        token = (token << 8U) | bytes[index];
    }
    return token;
}

void serialize_token(std::uint64_t token,
                     std::array<std::uint8_t, SERIALIZED_SIZE>& bytes,
                     const std::size_t offset)
{
    for (std::size_t index{0U}; index < TOKEN_SIZE; ++index)
    {
        bytes[offset + TOKEN_SIZE - index - 1U] =
            static_cast<std::uint8_t>(token & 0xFFU);
        token >>= 8U;
    }
}

std::uint32_t decode_level(
    const std::array<std::uint64_t, PlayerProgress::LEVEL_COUNT>& tokens,
    const std::uint64_t token)
{
    for (std::size_t index{0U}; index < tokens.size(); ++index)
    {
        if (tokens[index] == token)
        {
            return static_cast<std::uint32_t>(index + 1U);
        }
    }
    return 0U;
}

void remove_temporary_file(const std::filesystem::path& path) noexcept
{
    std::error_code error;
    std::filesystem::remove(path, error);
}

void report_save_error(const char* message) noexcept
{
#ifdef _WIN32
    OutputDebugStringA(message);
    OutputDebugStringA("\n");
#else
    std::fputs(message, stderr);
    std::fputc('\n', stderr);
#endif
}

bool replace_file(const std::filesystem::path& source,
                  const std::filesystem::path& destination) noexcept
{
#ifdef _WIN32
    return MoveFileExW(source.c_str(),
                       destination.c_str(),
                       MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
#else
    return std::rename(source.c_str(), destination.c_str()) == 0;
#endif
}

} // namespace

PlayerProgress::PlayerProgress() : PlayerProgress{default_save_path()}
{
}

PlayerProgress::PlayerProgress(std::filesystem::path save_path)
    : save_path_{std::move(save_path)}
{
    load();
}

std::uint32_t PlayerProgress::farthest_level() const noexcept
{
    return farthest_level_;
}

std::uint32_t PlayerProgress::last_visited_level() const noexcept
{
    return last_visited_level_;
}

void PlayerProgress::visit(const std::uint32_t level) noexcept
{
    if (level == 0U || level > LEVEL_COUNT)
    {
        return;
    }

    const bool changed{level != last_visited_level_ || level > farthest_level_};
    if (level > farthest_level_)
    {
        farthest_level_ = level;
    }
    last_visited_level_ = level;
    save_pending_ = save_pending_ || changed;

    if (save_pending_)
    {
        save_pending_ = !save();
    }
}

std::filesystem::path PlayerProgress::default_save_path()
{
#ifdef _WIN32
    const wchar_t* const local_app_data{::_wgetenv(L"LOCALAPPDATA")};
    if (local_app_data == nullptr || local_app_data[0] == L'\0')
    {
        return {};
    }
    return std::filesystem::path{local_app_data} / "Dreamscape" / "TheResidual" /
           "progress.dat";
#else
    const char* const xdg_data_home{std::getenv("XDG_DATA_HOME")};
    if (xdg_data_home != nullptr && xdg_data_home[0] != '\0')
    {
        const std::filesystem::path xdg_data_path{xdg_data_home};
        if (xdg_data_path.is_absolute())
        {
            return xdg_data_path / "the-residual" / "progress.dat";
        }
    }

    const char* const home{std::getenv("HOME")};
    if (home == nullptr || home[0] == '\0')
    {
        return {};
    }
    return std::filesystem::path{home} / ".local" / "share" / "the-residual" /
           "progress.dat";
#endif
}

void PlayerProgress::load() noexcept
{
    farthest_level_ = 0U;
    last_visited_level_ = 0U;
    save_pending_ = false;
    if (save_path_.empty())
    {
        return;
    }

    try
    {
        std::ifstream input{save_path_, std::ios::binary};
        if (!input)
        {
            return;
        }

        std::array<std::uint8_t, SERIALIZED_SIZE + 1U> stored_bytes{};
        input.read(reinterpret_cast<char*>(stored_bytes.data()),
                   static_cast<std::streamsize>(stored_bytes.size()));
        const std::streamsize byte_count{input.gcount()};
        if (input.bad())
        {
            return;
        }

        if (byte_count == static_cast<std::streamsize>(LEGACY_SERIALIZED_SIZE))
        {
            const std::uint32_t legacy_level{
                decode_level(FARTHEST_LEVEL_TOKENS, deserialize_token(stored_bytes, 0U))};
            if (legacy_level != 0U)
            {
                farthest_level_ = legacy_level;
                last_visited_level_ = legacy_level;
                save_pending_ = true;
            }
            return;
        }

        if (byte_count != static_cast<std::streamsize>(SERIALIZED_SIZE))
        {
            return;
        }

        const std::uint32_t farthest{
            decode_level(FARTHEST_LEVEL_TOKENS, deserialize_token(stored_bytes, 0U))};
        const std::uint32_t last_visited{decode_level(
            LAST_VISITED_TOKENS, deserialize_token(stored_bytes, TOKEN_SIZE))};
        if (farthest == 0U || last_visited == 0U || last_visited > farthest)
        {
            return;
        }

        farthest_level_ = farthest;
        last_visited_level_ = last_visited;
    }
    catch (...)
    {
        farthest_level_ = 0U;
        last_visited_level_ = 0U;
        save_pending_ = false;
    }
}

bool PlayerProgress::save() const noexcept
{
    if (farthest_level_ == 0U || farthest_level_ > LEVEL_COUNT ||
        last_visited_level_ == 0U || last_visited_level_ > LEVEL_COUNT ||
        last_visited_level_ > farthest_level_)
    {
        report_save_error("PlayerProgress: refusing to save invalid progress");
        return false;
    }

    if (save_path_.empty())
    {
        report_save_error("PlayerProgress: user data directory is unavailable");
        return false;
    }

    try
    {
        const std::filesystem::path directory{save_path_.parent_path()};
        if (!directory.empty())
        {
            std::error_code error;
            std::filesystem::create_directories(directory, error);
            if (error)
            {
                report_save_error("PlayerProgress: failed to create the save directory");
                return false;
            }
        }

        std::filesystem::path temporary_path{save_path_};
        temporary_path += ".tmp";
        std::array<std::uint8_t, SERIALIZED_SIZE> bytes{};
        serialize_token(FARTHEST_LEVEL_TOKENS[farthest_level_ - 1U], bytes, 0U);
        serialize_token(LAST_VISITED_TOKENS[last_visited_level_ - 1U], bytes, TOKEN_SIZE);

        std::ofstream output{temporary_path, std::ios::binary | std::ios::trunc};
        if (!output)
        {
            remove_temporary_file(temporary_path);
            report_save_error("PlayerProgress: failed to open the temporary save file");
            return false;
        }

        output.write(reinterpret_cast<const char*>(bytes.data()),
                     static_cast<std::streamsize>(bytes.size()));
        output.flush();
        output.close();
        if (!output)
        {
            remove_temporary_file(temporary_path);
            report_save_error("PlayerProgress: failed to write the temporary save file");
            return false;
        }

        if (!replace_file(temporary_path, save_path_))
        {
            remove_temporary_file(temporary_path);
            report_save_error("PlayerProgress: failed to replace the save file");
            return false;
        }

        return true;
    }
    catch (...)
    {
        report_save_error("PlayerProgress: unexpected error while saving progress");
        return false;
    }
}
