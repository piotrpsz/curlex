/*
 *  MIT License
 *
 *  Copyright (c) 2024 Piotr Pszczółkowski
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 *  Project: curlex
 *  Author: Piotr Pszczółkowski (piotr@beesoft.pl)
 *  Created: 2024/09/10
 */
#pragma once

/*------- include files:
-------------------------------------------------------------------*/
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
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