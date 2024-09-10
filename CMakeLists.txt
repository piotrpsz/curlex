cmake_minimum_required(VERSION 3.29)
project(curlex)

set(CMAKE_CXX_STANDARD 20)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(fmt REQUIRED)

include(FetchContent)
FetchContent_Declare(
        glaze
        GIT_REPOSITORY https://github.com/stephenberry/glaze.git
        GIT_TAG main
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glaze)


add_library(curlex STATIC
        curlex.cc curlex.h
        version_info.cc
        version_info.h
        shared.h
        guard.h
        response.h
        request.cc
        request.h
)

target_include_directories(curlex PUBLIC
        fmt
)
target_link_libraries(curlex PUBLIC
        fmt::fmt
        glaze::glaze
        curl
)
