//
// Created by Piotr Pszczółkowski on 10/09/2024.
//

#pragma once
#include <curl/curl.h>

class Guard {
    CURL* handle_;
public:
    explicit Guard(CURL* handle) : handle_{handle} {}
    ~Guard() {
        // Reset the handle on exit.
        curl_easy_reset(handle_);
    }
};
