cmake_minimum_required(VERSION 3.21)
project(low-latency
    VERSION 0.1.0
    LANGUAGES CXX
    DESCRIPTION "Modern C++20 development environment"
)

# ── C++20 everywhere ──────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)          # -std=c++20, not -std=gnu++20

# ── Export compile_commands.json for clangd ───────────────────────
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ── Warnings (treat your code like it's going to prod) ────────────
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(
        -Wall -Wextra -Wpedantic
        -Wshadow -Wconversion -Wsign-conversion
        -Wnull-dereference -Wdouble-promotion
        -Wformat=2
    )
endif()

# ── Main executable ───────────────────────────────────────────────
add_executable(low-latency src/main.cpp)
target_include_directories(low-latency PRIVATE include)

# ── Tests ─────────────────────────────────────────────────────────
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)

    add_executable(tests tests/hello_test.cpp)
    target_include_directories(tests PRIVATE include)
    target_link_libraries(tests PRIVATE GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
