cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE RELEASE)
add_compile_options(-Wall -Wextra -pedantic -Werror -fmodules-ts)

project(vvchess VERSION 0.1)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
