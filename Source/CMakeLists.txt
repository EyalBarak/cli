cmake_minimum_required(VERSION 3.16)
project(cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

add_compile_options(-O0 -g3)
#add_compile_options(-O3 -DNDEBUG)

add_library(cli_lib ../Include/cli.h ../Include/Detail/abstract_command.h
        Detail/abstract_command.cpp ../Include/Detail/generic_command.h
        ../Include/Detail/menu.h Detail/menu.cpp ../Include/Detail/app.h Detail/app.cpp ../Include/Detail/argument_handler.h ../Include/Detail/simple_command.h Detail/simple_command.cpp ../Include/Detail/cli_exceptions.h Detail/cli_exceptions.cpp)