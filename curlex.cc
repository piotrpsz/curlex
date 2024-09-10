//
// Created by Piotr Pszczółkowski on 10/09/2024.
//

#include "curlex.h"
#include "guard.h"
#include <fmt/core.h>


//-------------------------------------------------------------------
/// Execute GET command for the request.
/// \param req - request to execute
/// \return optional response with data received from the server.
//-------------------------------------------------------------------
std::optional<Response> Curlex::GET(Request const& req) const noexcept {
    // Guarantees CURL handle reset upon exiting the function.
    Guard guard(handle_);

    auto body_buffer_ptr = set_data_buffer();
    auto headers_buffer_ptr = set_headers_buffer();
    struct curl_slist* const headers = set_headers_list(req.headers());

    // Set option GET.
    if (auto err = curl_easy_setopt(handle_, CURLOPT_HTTPGET, 1); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Set URL.
    if (auto err = curl_easy_setopt(handle_, CURLOPT_URL, req.url().c_str()); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Set the verbose option if the request says so
    if (req.is_verbose())
        if (auto err = curl_easy_setopt(handle_, CURLOPT_VERBOSE, 1L); err) {
            fmt::print(stderr, "{}\n", curl_easy_strerror(err));
            return {};
        }
    // And run
    if (auto err = curl_easy_perform(handle_); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Getting the response code sent by the server.
    long code{};
    if (auto err = curl_easy_getinfo(handle_, CURLINFO_RESPONSE_CODE, &code); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Release manually memory allocated for headers if they were used.
    if (headers)
        curl_slist_free_all(headers);
    // Data and header buffers should free memory automatically.

    return Response(code)
            .body(std::move(*body_buffer_ptr))
            .headers(std::move(*headers_buffer_ptr));
}

//-------------------------------------------------------------------
/// Execute POST command for the request.
/// \param req - request to execute
/// \return optional response with data received from the server.
//-------------------------------------------------------------------
std::optional<Response> Curlex::POST(Request const& req) const noexcept {
    // Guarantees CURL handle reset upon exiting the function.
//    Guard guard(handle_);

    auto body_buffer_ptr = set_data_buffer();
    auto headers_buffer_ptr = set_headers_buffer();
    struct curl_slist* const headers = set_headers_list(req.headers());

    // Set option POST.
    if (auto err = curl_easy_setopt(handle_, CURLOPT_HTTPPOST, 1); err) {
        fmt::print(stderr, "POST: {}\n", curl_easy_strerror(err));
        return {};
    }

    // Set option URL.
    if (auto err = curl_easy_setopt(handle_, CURLOPT_URL, req.url().c_str()); err) {
        fmt::print(stderr, "POST: {}\n", curl_easy_strerror(err));
        return {};
    }

    Data data{};
    if (!req.data().empty()) {
        data.ptr = req.data().c_str();
        data.left = req.data().size();

        if (auto const err = curl_easy_setopt(handle_, CURLOPT_READFUNCTION, data_reader); err) {
            fmt::print(stderr, "{}\n", curl_easy_strerror(err));
            return {};
        }
        if (auto const err = curl_easy_setopt(handle_, CURLOPT_READDATA, &data); err) {
            fmt::print(stderr, "{}\n", curl_easy_strerror(err));
            return {};
        }
        if (auto const err = curl_easy_setopt(handle_, CURLOPT_POSTFIELDSIZE, req.data().size()); err) {
            fmt::print(stderr, "{}\n", curl_easy_strerror(err));
            return {};
        }
    }

    // Set the verbose option if the request says so
    if (req.is_verbose())
        if (auto err = curl_easy_setopt(handle_, CURLOPT_VERBOSE, 1L); err) {
            fmt::print(stderr, "{}\n", curl_easy_strerror(err));
            return {};
        }
    // And run
    if (auto err = curl_easy_perform(handle_); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Getting the response code sent by the server.
    long code{};
    if (auto err = curl_easy_getinfo(handle_, CURLINFO_RESPONSE_CODE, &code); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Release manually memory allocated for headers if they were used.
    if (headers)
        curl_slist_free_all(headers);
    // Data and header buffers should free memory automatically.

    return Response(code)
            .body(std::move(*body_buffer_ptr))
            .headers(std::move(*headers_buffer_ptr));
}

//-------------------------------------------------------------------
/// Execute OPTIONS command for the request.
/// \param req - request to execute
/// \return optional response with data received from the server.
//-------------------------------------------------------------------
std::optional<Response> Curlex::OPTIONS(Request const& req) const noexcept {
    // Guarantees CURL handle reset upon exiting the function.
    Guard guard(handle_);

    auto body_buffer_ptr = set_data_buffer();
    auto headers_buffer_ptr = set_headers_buffer();
    struct curl_slist* const headers = set_headers_list(req.headers());

    // Set option OPTIONS
    if (auto err = curl_easy_setopt(handle_, CURLOPT_CUSTOMREQUEST, "OPTIONS"); err) {
        fmt::print(stderr, "{}\n", curl_easy_strerror(err));
        return {};
    }
    // Set URL.
    if (auto err = curl_easy_setopt(handle_, CURLOPT_URL, req.url().c_str()); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Set the verbose option if the request says so
    if (req.is_verbose())
        if (auto err = curl_easy_setopt(handle_, CURLOPT_VERBOSE, 1L); err) {
            fmt::print(stderr, "{}\n", curl_easy_strerror(err));
            return {};
        }
    // And run
    if (auto err = curl_easy_perform(handle_); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Getting the response code sent by the server.
    long code{};
    if (auto err = curl_easy_getinfo(handle_, CURLINFO_RESPONSE_CODE, &code); err) {
        fmt::print(stderr, "GET: {}\n", curl_easy_strerror(err));
        return {};
    }
    // Release manually memory allocated for headers if they were used.
    if (headers)
        curl_slist_free_all(headers);
    // Data and header buffers should free memory automatically.

    return Response(code)
            .body(std::move(*body_buffer_ptr))
            .headers(std::move(*headers_buffer_ptr));
}


/********************************************************************
*                                                                   *
*                         P R I V A T E                             *
*                                                                   *
********************************************************************/

/// Allocation and registration a buffer in the system for received
/// body data and registration of the function for saving them.
/// \return shared pointer to allocated memory.
std::shared_ptr<std::string> Curlex::set_data_buffer() const noexcept {
    if (auto err = curl_easy_setopt(handle_, CURLOPT_WRITEFUNCTION, collector); err) {
        fmt::print(stderr, "{}\n", curl_easy_strerror(err));
        return {};
    }
    auto ptr = std::make_shared<std::string>();
    if (auto err = curl_easy_setopt(handle_, CURLOPT_WRITEDATA, ptr.get()); err) {
        fmt::print(stderr, "{}\n", curl_easy_strerror(err));
        return {};
    }
    return ptr;
}

/// Allocation and registration a buffer in the system for received
/// headers data and registration of the function for saving them.
/// \return shared pointer to allocated memory.
std::shared_ptr<std::string> Curlex::set_headers_buffer() const noexcept {
    if (auto err = curl_easy_setopt(handle_, CURLOPT_HEADERFUNCTION, collector); err) {
        fmt::print(stderr, "{}\n", curl_easy_strerror(err));
        return {};
    }
    auto ptr = std::make_shared<std::string>();
    if (auto err = curl_easy_setopt(handle_, CURLOPT_HEADERDATA, ptr.get()); err) {
        fmt::print(stderr, "{}\n", curl_easy_strerror(err));
        return {};
    }
    return ptr;
}

/// Create curl's list with headers,
/// \param headers - user defined vector of pairs key-value.
/// \return pointer to internally allocated curl's list.
/// \remark the memory of the list must be manually released.
struct curl_slist* Curlex::set_headers_list(std::vector<std::pair<std::string, std::string>> const& headers) const noexcept {
    if (headers.empty()) return {};
    struct curl_slist* list = nullptr;

    for (auto const& pair : headers) {
        auto [k, v] = pair;
        auto const text = fmt::format("{}:{}", k, v);
        list = curl_slist_append(list, text.c_str());
    }
    if (auto err = curl_easy_setopt(handle_, CURLOPT_HTTPHEADER, list); err) {
        fmt::print(stderr, "{}\n", curl_easy_strerror(err));
        return {};
    }
    return list;
}


/// A static function that adds the specified data to a buffer that is a string.
/// \param src - pointer to the buffer with the data to be saved
/// \param one_item_size - size of one copied item (normally 1 for bytes),
/// \param items_count - how many itams to copy (number of bytes - one_item_size * items_count).
/// \return number of copied bytes.
size_t Curlex::collector(char const *const src, size_t one_item_size, size_t const items_count, void *const dst) noexcept {
    auto const string = reinterpret_cast<std::string *>(dst);
    auto const n = one_item_size * items_count;
    string->append(src, n);
    return n;
};

/// Copy data from source to destination.
/// \param dst - copy destination,
/// \param one_item_size - size one item in bytes (normally 1 for bytes),
/// \param items_count - how many items to copy  (number of bytes := one_item_size * items_count),
/// \param src - from where copy
/// \return number of copied bytes.
size_t Curlex::data_reader(char* const dst, size_t const one_item_size, size_t const items_count, void* const src) noexcept {
    auto data = reinterpret_cast<struct Data*>(src);
    size_t const max_bytes_to_copy = one_item_size * items_count;

    if (data->left) {
        auto const n = (data->left > max_bytes_to_copy) ? max_bytes_to_copy : data->left;
        memcpy(dst, data->ptr, n);

        data->ptr += n;
        data->left -= n;
        return n;
    }
    return 0;
}