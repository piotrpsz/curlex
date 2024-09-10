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
#include <string>
#include <vector>
#include <utility>
#include <variant>


class Request {
    using KeyValueVec = std::vector<std::pair<std::string, std::string>>;
    std::string scheme_{"https"};   // default schema
    std::string host_{};
    std::string endpoint_{};
    std::string data_{};
    KeyValueVec params_{};
    std::string body_;
    KeyValueVec headers_{};
    bool verbose_{};
    std::string url_{};
public:
    Request() = default;
    Request& scheme(std::string const& text) noexcept {
        scheme_ = text;
        return *this;
    }
    Request& host(std::string const& text) noexcept {
        host_ = text;
        return *this;
    }
    Request& endpoint(std::string const& text) noexcept {
        endpoint_ = text;
        return *this;
    }
    Request& data(std::string const& text) noexcept {
        data_ = text;
        return *this;
    }
    [[nodiscard]] std::string const& data() const noexcept {
        return data_;
    }

    /// Add a param.
    /// When all params are added call 'build()'.
    /// After that, the whole URL can you obtain via 'product()'.
    Request& add_param(std::string const& k, std::variant<std::string, int64_t, double_t> v) noexcept;

    /// Remove all params and product.
    Request& reset_params() noexcept {
        params_ = {};
        url_ = {};
        return *this;
    }

    Request& body(std::string const& text) noexcept {
        body_ = text;
        return *this;
    }
    [[nodiscard]] std::string const& body() const noexcept {
        return body_;
    }
    /// Build the URL using all components and params.
    Request& build() noexcept;

    /// Return the URL.
    [[nodiscard]] std::string const& url() const noexcept {
        return url_;
    }

    Request& add_header(std::string const& k, std::variant<std::string, int64_t, double_t> v) noexcept;
    KeyValueVec const& headers()  const noexcept {
        return headers_;
    }
    Request& verbose() noexcept {
        verbose_ = true;
        return *this;
    }
    [[nodiscard]] bool is_verbose() const noexcept {
        return verbose_;
    }
private:
    static bool exists(KeyValueVec const& vec, std::string const& key) noexcept;
    static std::string as_string(std::variant<std::string, int64_t, double_t> v) noexcept;
};