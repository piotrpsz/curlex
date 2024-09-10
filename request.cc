//
// Created by Piotr Pszczółkowski on 10/09/2024.
//

#include "request.h"
#include <span>
#include <utility>
#include <fmt/core.h>

Request& Request::build() noexcept {
    url_ = fmt::format("{}://{}/{}", scheme_, host_, endpoint_);
    if (!params_.empty()) {
        std::span span{params_};
        auto [k, v] = span.front();
        url_ += fmt::format("?{}={}", k, v);
        span = span.subspan(1);

        while (!span.empty()) {
            auto [k, v] = span.front();
            url_ += fmt::format("&{}={}", k, v);
            span = span.subspan(1);
        }
    }
    return *this;
}

Request& Request::add_param(std::string const& k, std::variant<std::string, int64_t, double_t> v) noexcept {
    if (!k.empty()) {
        if (!exists(params_, k)) params_.emplace_back(k, as_string(std::move(v)));
        else fmt::print(stderr, "Repeated parameter key not accepted ({})", k);
    }
    return *this;
}

Request& Request::add_header(std::string const& k, std::variant<std::string, int64_t, double_t> v) noexcept {
    if (!k.empty()) {
        if (!exists(headers_, k)) headers_.emplace_back(k, as_string(std::move(v)));
        else fmt::print(stderr, "Repeated header key not accepted ({})", k);
    }
    return *this;
}

/********************************************************************
*                                                                   *
*                         P R I V A T E                             *
*                                                                   *
********************************************************************/


bool Request::exists(KeyValueVec const& vec, std::string const& key) noexcept {
    for (auto const& pair : vec) {
        auto  [key_in_vec, _] = pair;
        if (key_in_vec == key)
            return true;
    }
    return {};
}

std::string Request::as_string(std::variant<std::string, int64_t, double_t> v) noexcept {
    std::string value{};
    switch (v.index()) {
        case 0:
            value = std::get<std::string>(v);
            break;
        case 1:
            value = std::to_string(std::get<int64_t>(v));
            break;
        case 2:
            value = std::to_string(std::get<double_t>(v));
            break;
    }
    return value;
}
