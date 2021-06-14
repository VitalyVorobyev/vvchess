cmake_minimum_required(VERSION 3.15)

set(cmake_c_compiler "/usr/bin/gcc-11")
set(cmake_cxx_compiler "/usr/bin/g++-11")
set(cmake_cxx_standard 20)
set(cmake_cxx_standard_required True)

add_compile_options(-Wall -Wextra -pedantic -Werror -fmodules-ts)

project(vvchess VERSION 0.1)

add_executable(vvchess
    src/definitions.cpp
    src/magicfinder.cpp
    src/main.cpp
)

target_include_directories(vvchess PUBLIC src)
