//
// Created by Piotr Pszczółkowski on 10/09/2024.
//

#include "version_info.h"
#include "shared.h"
#include <curl/curl.h>
#include <string_view>
#include <algorithm>


VersionInfo::VersionInfo() {
    auto const info = curl_version_info(CURLVERSION_NOW);
    edition = info->age + 1;
    curl_version = info->version;
    version_number = info->version_num;
    host = info->host;

    if (info->ssl_version)
        ssl_version = info->ssl_version;
    if (info->libz_version)
        libz_version = info->libz_version;

    if (info->protocols) {
        for (auto it = info->protocols; *it != nullptr; it++)
            protocols.emplace_back(*it);
        std::sort(protocols.begin(), protocols.end(),
                  [] (std::string_view s0, std::string_view s1)  {
                      return shared::to_lower(s0) < shared::to_lower(s1);
                  });
    }

    if (info->feature_names) {
        for (auto it = info->feature_names; *it; ++it)
            feature_names.emplace_back(*it);
        std::sort(feature_names.begin(), feature_names.end(),
                  [] (std::string_view s0, std::string_view s1)  {
                      return shared::to_lower(s0) < shared::to_lower(s1);
                  });
    }

    if (info->ares) {
        ares = info->ares;
        ares_number = info->ares_num;
    }
    if (info->libidn)
        libidn = info->libidn;
    icon_ver_number = info->iconv_ver_num;
    if (info->libssh_version)
        libssh_version = info->libssh_version;
    if (info->brotli_version) {
        brotli_version = info->brotli_version;
        brotli_ver_number = info->brotli_ver_num;
    }
    if (info->nghttp2_version) {
        nghttp2_version = info->nghttp2_version;
        nghttp2_ver_number = info->nghttp2_ver_num;
    }
    if (info->quic_version)
        quic_version = info->quic_version;
    if (info->cainfo)
        ca_info = info->cainfo;
    if (info->capath)
        ca_path = info->capath;
    if (info->zstd_version) {
        zstd_version = info->zstd_version;
        zstd_ver_number = info->zstd_ver_num;
    }
    if (info->hyper_version)
        hyper_version = info->hyper_version;
    if (info->gsasl_version)
        gsasl_version = info->gsasl_version;
}

std::string VersionInfo::as_json() const {
    auto json = glz::write_json(this).value_or("glaze error");
    return glz::prettify_json(json);
}

void VersionInfo::print() const noexcept {
    fmt::print("curl info {{\n");
    fmt::print("\t           edition: {}\n", edition);
    fmt::print("\t           version: {} ({})\n", curl_version, version_number);
    fmt::print("\t              host: {}\n", host);

    if (!ssl_version.empty())
        fmt::print("\t       ssl version: {}\n", ssl_version);
    if (!libz_version.empty())
        fmt::print("\t      libz version: {}\n", libz_version);
    if (not ares.empty()) {
        fmt::print("\t              ares: {}\n", ares);
        fmt::print("\t       ares number: {}\n", ares_number);
    }
    if (not libidn.empty())
        fmt::print("\t            libidn: {}\n", libidn);
    if (icon_ver_number)
        fmt::print("\t   icon ver number: {}\n", icon_ver_number);
    if (not libssh_version.empty())
        fmt::print("\t    libssh version: {}\n", libssh_version);
    if (not brotli_version.empty()) {
        fmt::print("\t    brotli version: {}\n", brotli_version);
        fmt::print("\t brotli ver number: {}\n", brotli_ver_number);
    }
    if (not nghttp2_version.empty()) {
        fmt::print("\t   nghttp2 version: {}\n", nghttp2_version);
        fmt::print("\tnghttp2 ver number: {}\n", nghttp2_ver_number);
    }
    if (not quic_version.empty())
        fmt::print("\t quic version: {}\n", quic_version);
    if (not ca_info.empty())
        fmt::print("\t           CA info: {}\n", ca_info);
    if (not ca_path.empty())
        fmt::print("\t           CA path: {}\n", ca_path);
    if (not zstd_version.empty()) {
        fmt::print("\t      zstd version: {}\n", zstd_version);
        fmt::print("\t   zstd ver number: {}\n", zstd_ver_number);
    }
    if (!hyper_version.empty())
        fmt::print("\t     hyper version: {}\n", hyper_version);
    if (!gsasl_version.empty())
        fmt::print("\t     gsasl version: {}\n", gsasl_version);

    fmt::print("\t         protocols: {}\n", shared::join(protocols));
    fmt::print("\t          features: {}\n", shared::join(feature_names));
    fmt::print("}}\n");
}
