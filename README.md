# C++ wrapper for the well-known curl library (written in C).

### Code example
```c++
Curlex cx;
fmt::print("curl version: {}\n", cx.version());
test(cx)
......

void test(Curlex& cx) {
    auto request = Request()
            .scheme("http")
            .host("127.0.0.1:3030")
            .endpoint("questions")
            .add_param("start", "1")
            .add_param("end", "400")
            .build();

    if (auto response = cx.GET(request); response) {
        fmt::print("-------------------------------------------\n");
        fmt::print("response code: {}\n", response->code());
        fmt::print("response headers:\n");
        for (auto it: response->headers())
            fmt::print("\t{}\n", it);
        fmt::print("-------------------------------------------\n");
        fmt::print("response body:\n");
        fmt::print("{}\n", response->body());
    }
}
```