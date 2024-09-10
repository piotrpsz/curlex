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
#include <glaze/glaze.hpp>

struct VersionInfo {
public:
    int edition{};
    std::string curl_version{};
    int version_number{};
    std::string host{};
    std::string ssl_version{};
    std::string libz_version{};
    std::vector<std::string> protocols{};
    std::string ares{};
    int ares_number{};
    std::string libidn{};
    int icon_ver_number{};
    std::string libssh_version{};
    std::string brotli_version{};
    uint brotli_ver_number{};
    std::string nghttp2_version{};
    uint nghttp2_ver_number{};
    std::string quic_version{};
    std::string ca_info{};
    std::string ca_path{};
    std::string zstd_version{};
    uint zstd_ver_number{};
    std::string hyper_version{};
    std::string gsasl_version{};
    std::vector<std::string> feature_names;

    struct glaze {
        using T = VersionInfo;
        static constexpr auto value = glz::object(
                &T::edition,
                &T::curl_version,
                &T::version_number,
                &T::host,
                &T::ssl_version,
                &T::libz_version,
                &T::protocols,
                &T::ares,
                &T::ares_number,
                &T::libidn,
                &T::icon_ver_number,
                &T::libssh_version,
                &T::brotli_version,
                &T::brotli_ver_number,
                &T::nghttp2_version,
                &T::nghttp2_ver_number,
                &T::quic_version,
                &T::ca_info,
                &T::ca_path,
                &T::zstd_version,
                &T::zstd_ver_number,
                &T::hyper_version,
                &T::gsasl_version,
                &T::feature_names
        );
    };

    VersionInfo();
    [[nodiscard]] std::string as_json() const;
    void print() const noexcept;

    std::string version() && {
        return std::move(curl_version);
    }
    [[nodiscard]] std::string const& version() const& {
        return curl_version;
    }

};
