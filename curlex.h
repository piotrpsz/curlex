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
#include <curl/curl.h>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <optional>
#include "version_info.h"
#include "request.h"
#include "response.h"

class Curlex {
    CURL* handle_;
    struct Data { char const* ptr; size_t left; };
public:
    Curlex() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        handle_ = curl_easy_init();
    }
    ~Curlex() {
        curl_easy_cleanup(handle_);
        curl_global_cleanup();
    }

    [[nodiscard]] std::string version() const noexcept {
        return VersionInfo().version();
    }
    [[nodiscard]] VersionInfo info() const noexcept {
        return {};
    }
    [[nodiscard]] Curlex clone() const {
        return Curlex(curl_easy_duphandle(handle_));
    }
    void quick_exit() const {
        curl_easy_setopt(handle_, CURLOPT_QUICK_EXIT, 1L);
    }

    [[nodiscard]] std::optional<Response> GET(Request const& req) const noexcept;
    [[nodiscard]] std::optional<Response> POST(Request const& req) const noexcept;
    [[nodiscard]] std::optional<Response> OPTIONS(Request const& req) const noexcept;

private:
    explicit Curlex(CURL* handle) : handle_{handle} {}

    [[nodiscard]] std::shared_ptr<std::string> set_data_buffer() const noexcept;
    [[nodiscard]] std::shared_ptr<std::string> set_headers_buffer() const noexcept;
    [[nodiscard]] struct curl_slist* set_headers_list(std::vector<std::pair<std::string, std::string>> const& headers) const noexcept;

    static size_t collector(char const* src, size_t one_item_size, size_t items_count, void* dst) noexcept;
    static size_t data_reader(char* dst, size_t one_item_size, size_t items_count, void* src) noexcept;
};
