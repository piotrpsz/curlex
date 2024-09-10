//
// Created by Piotr Pszczółkowski on 10/09/2024.
//

#pragma once

#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <fmt/core.h>

namespace shared {
    static inline bool is_not_space(char c) noexcept {
        return not std::isspace(c);
    }

    static inline std::string trim_left(std::string s) noexcept {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), is_not_space));
        return s;
    }

    static inline std::string trim_right(std::string s) noexcept {
        s.erase(std::find_if(s.rbegin(), s.rend(), is_not_space).base(), s.end());
        return s;
    }

    static inline std::string trim(std::string s) noexcept {
        return trim_left(trim_right(std::move(s)));
    }

    static inline std::vector<std::string> split(std::string const &text, char const delimiter) noexcept {
        auto const n = std::accumulate(
                text.cbegin(),
                text.cend(),
                ssize_t {0},
                [delimiter](ssize_t const count, char const c) {
                    return (c == delimiter) ? count + 1 : count;
                }
        );

        std::vector<std::string> tokens{};
        tokens.reserve(n + 1);

        std::string token;
        std::istringstream stream(text);
        while (std::getline(stream, token, delimiter))
            if (auto str = trim(token); !str.empty())
                tokens.push_back(str);
        return tokens;
    }

    static inline std::string join(std::vector<std::string> const& data, char delimiter = ',') noexcept {
        return std::accumulate(
                std::next(data.begin()),
                data.end(),
                data[0],
                [delimiter](std::string a, std::string b) {
                    return fmt::format("{}{}{}", std::move(a), delimiter, std::move(b));
                }
        );
    }

    static inline std::string to_lower(std::string_view in) noexcept {
        std::string out;
        out.reserve(in.size());
        std::ranges::transform(in.begin(), in.end(), out.begin(),
                               [](auto c) {
                                   return static_cast<char>(std::tolower(c));
                               });
        return out;
    }
}
