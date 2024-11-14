cmake_minimum_required(VERSION 3.25)
project(cstrings_yurevych)

set(CMAKE_CXX_STANDARD 20)

set(SANITIZE_MEMORY FALSE)
set(SANITIZE_ADDRESS TRUE)
set(SANITIZE_THREAD FALSE)
set(SANITIZE_UNDEFINED FALSE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/sanitizers-cmake/cmake" ${CMAKE_MODULE_PATH})
find_package(Sanitizers)

add_executable(cstrings_yurevych my_str_t.cpp main.cpp)
add_sanitizers(cstrings_yurevych)

#

include(FetchContent)

# Externally provided libraries
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG main) # need main for benchmark::benchmark

FetchContent_MakeAvailable(
        googletest
        googlebenchmark)

add_executable(g_benchmark benchmark.cpp my_str_t.cpp)
target_link_libraries(g_benchmark benchmark::benchmark)