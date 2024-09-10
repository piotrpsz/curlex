//
// Created by Piotr Pszczółkowski on 10/09/2024.
//

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
