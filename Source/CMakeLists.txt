set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Werror -Wextra -Wpedantic)

add_compile_options(-O0 -g3)
#add_compile_options(-O3 -DNDEBUG)

add_library(cli_lib ../Include/cli.h ../Include/Detail/abstract_command.h Detail/abstract_command.cpp ../Include/Detail/generic_command.h ../Include/Detail/menu.h Detail/menu.cpp)