cmake_minimum_required(VERSION 3.15)

set(cmake_c_compiler /usr/bin/gcc-11)
set(cmake_cxx_compiler /usr/bin/g++-11)
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

enable_testing()

add_executable(test_pop_first_one
    src/definitions.cpp
    src/magicfinder.cpp
    test/test_pop_first_one.cpp
)

add_executable(test_count_ones
    src/definitions.cpp
    src/magicfinder.cpp
    test/test_count_ones.cpp
)

add_executable(test_bishop_mask
    src/definitions.cpp
    src/magicfinder.cpp
    test/test_bishop_mask.cpp
)

add_test(test_pop_first_one ./test_pop_first_one)
add_test(test_count_ones ./test_count_ones)
add_test(test_bishop_mask ./test_bishop_mask)

