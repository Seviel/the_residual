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

constexpr std::size_t SERIALIZED_SIZE{8U};
constexpr std::array<std::uint64_t, PlayerProgress::LEVEL_COUNT> LEVEL_TOKENS{
    0xDB0BC1B23EFFEE58ULL, 0xAB155E118124C69EULL, 0xBA41F2549F047FC4ULL,
    0x0BFEA0C779E4146FULL, 0xA0446638F5F06273ULL, 0xFB5EBB9B30B4C948ULL,
    0x538EE11C9386E481ULL, 0x4494F78212FC7982ULL, 0xD5F78DD5BDF558E6ULL,
    0xD4F52DB3840DF62BULL, 0x682880822B0870F2ULL, 0x2F856D4521DE2CC0ULL,
    0x371CAE81D234ABFEULL, 0xF6212EC2AE56D78AULL, 0x8C76C9B4A9258A3CULL,
    0xB8CBED635EAA840CULL, 0x07F16171511ED1F3ULL, 0x63FB952BD120EACCULL,
    0x283EDAB430FD11E3ULL, 0x36AB355EFEB773C9ULL, 0x47BCADC2DD03A7B6ULL,
    0xF407ADAF0C8B327CULL, 0x582B8525430911C8ULL, 0xD24FF68950E5E86DULL};

constexpr bool level_tokens_are_valid()
{
    for (std::size_t index{0U}; index < LEVEL_TOKENS.size(); ++index)
    {
        if (LEVEL_TOKENS[index] == 0U)
        {
            return false;
        }

        for (std::size_t other_index{index + 1U}; other_index < LEVEL_TOKENS.size();
             ++other_index)
        {
            if (LEVEL_TOKENS[index] == LEVEL_TOKENS[other_index])
            {
                return false;
            }
        }
    }

    return true;
}

static_assert(level_tokens_are_valid(), "Every level must have a unique, nonzero save token");

std::uint64_t deserialize_token(const std::array<std::uint8_t, SERIALIZED_SIZE>& bytes)
{
    std::uint64_t token{0U};
    for (const std::uint8_t byte : bytes)
    {
        token = (token << 8U) | byte;
    }
    return token;
}

std::array<std::uint8_t, SERIALIZED_SIZE> serialize_token(std::uint64_t token)
{
    std::array<std::uint8_t, SERIALIZED_SIZE> bytes{};
    for (std::size_t index{0U}; index < bytes.size(); ++index)
    {
        bytes[bytes.size() - index - 1U] = static_cast<std::uint8_t>(token & 0xFFU);
        token >>= 8U;
    }
    return bytes;
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

void PlayerProgress::reach(const std::uint32_t level) noexcept
{
    if (level == 0U || level > LEVEL_COUNT || level < farthest_level_)
    {
        return;
    }

    if (level > farthest_level_)
    {
        farthest_level_ = level;
        save_pending_ = true;
    }

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
        if (input.gcount() != static_cast<std::streamsize>(SERIALIZED_SIZE) || input.bad())
        {
            return;
        }

        std::array<std::uint8_t, SERIALIZED_SIZE> token_bytes{};
        for (std::size_t index{0U}; index < token_bytes.size(); ++index)
        {
            token_bytes[index] = stored_bytes[index];
        }
        const std::uint64_t stored_token{deserialize_token(token_bytes)};

        for (std::size_t index{0U}; index < LEVEL_TOKENS.size(); ++index)
        {
            if (LEVEL_TOKENS[index] == stored_token)
            {
                farthest_level_ = static_cast<std::uint32_t>(index + 1U);
                return;
            }
        }
    }
    catch (...)
    {
        farthest_level_ = 0U;
    }
}

bool PlayerProgress::save() const noexcept
{
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
        const auto bytes{serialize_token(LEVEL_TOKENS[farthest_level_ - 1U])};

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
