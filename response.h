//
// Created by Piotr Pszczółkowski on 10/09/2024.
//

#pragma once
#include <string>
#include <vector>
#include "shared.h"

class Response {
    long code_;
    std::string body_;
    std::vector<std::string> headers_;
public:
    explicit Response(long const code) : code_{code} {
    }
    Response& body(std::string&& text) noexcept {
        body_ = std::move(text);
        return *this;
    }
    Response& headers(std::string&& text) noexcept {
        auto items = shared::split(text, '\n');
        for (auto&& str : items) {
            if (str.contains(':'))
                headers_.push_back(str);
        }
        std::sort(headers_.begin(), headers_.end(),
                  [] (std::string const& s0, std::string const& s1)  {
                      return std::lexicographical_compare(s0.begin(), s0.end(), s1.begin(), s1.end());
                  });
        return *this;
    }

    [[nodiscard]] long code() const noexcept {
        return code_;
    }
    [[nodiscard]] std::string const& body() const noexcept {
        return body_;
    }
    [[nodiscard]] std::vector<std::string> const& headers() const noexcept {
        return headers_;
    }
};