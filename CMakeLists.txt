cmake_minimum_required(VERSION 3.15)

set(CMAKE_BUILD_TYPE RELEASE)
add_compile_options(-O2 -Wall -Wextra -pedantic -Werror -fmodules-ts)

project(vvchess VERSION 0.1)

find_package(GTest REQUIRED)

add_executable(vvchess
    src/definitions.cpp src/magicfinder.cpp src/main.cpp
)

enable_testing()

add_executable(test_pop_first_one
    src/definitions.cpp src/magicfinder.cpp
    test/test_pop_first_one.cpp
)

add_executable(test_count_ones
    src/definitions.cpp src/magicfinder.cpp
    test/test_count_ones.cpp
)

add_executable(test_bishop_mask
    src/definitions.cpp src/magicfinder.cpp
    test/test_bishop_mask.cpp
)

add_executable(test_rook_mask
    src/definitions.cpp src/magicfinder.cpp
    test/test_rook_mask.cpp
)

target_link_libraries(test_pop_first_one gtest gtest_main pthread)
target_link_libraries(test_count_ones    gtest gtest_main pthread)
target_link_libraries(test_bishop_mask   gtest gtest_main pthread)
target_link_libraries(test_rook_mask     gtest gtest_main pthread)

# Doesn't work with modules :(
# include(GoogleTest)
# gtest_discover_tests(test_bishop_mask)

add_test(test_pop_first_one bintest/test_pop_first_one)
add_test(test_count_ones    bintest/test_count_ones)
add_test(test_bishop_mask   bintest/test_bishop_mask)
add_test(test_rook_mask     bintest/test_rook_mask)

set_target_properties(
    test_pop_first_one test_count_ones test_bishop_mask test_rook_mask
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bintest"
)
