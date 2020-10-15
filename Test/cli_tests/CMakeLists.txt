cmake_minimum_required(VERSION 3.16)
project(cli)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-O0 -g3)

add_executable(run_tests basic_tests.cpp)

target_link_libraries(run_tests gtest gtest_main cli_lib)