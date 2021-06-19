find_package(GTest REQUIRED)

add_compile_options(-O0)

add_executable(test_pop_first_one
    ../src/definitions.cpp ../src/bbtools.cpp
    test_pop_first_one.cpp
)

add_executable(test_count_ones
    ../src/definitions.cpp ../src/bbtools.cpp
    test_count_ones.cpp
)

add_executable(test_bishop_mask
    ../src/definitions.cpp ../src/bbtools.cpp
    test_bishop_mask.cpp
)

add_executable(test_rook_mask
    ../src/definitions.cpp ../src/bbtools.cpp
    test_rook_mask.cpp
)

target_link_libraries(test_pop_first_one gtest gtest_main pthread)
target_link_libraries(test_count_ones    gtest gtest_main pthread)
target_link_libraries(test_bishop_mask   gtest gtest_main pthread)
target_link_libraries(test_rook_mask     gtest gtest_main pthread)

# Doesn't work with modules :(
# include(GoogleTest)
# gtest_discover_tests(test_bishop_mask)

add_test(test_pop_first_one test_pop_first_one)
add_test(test_count_ones    test_count_ones)
add_test(test_bishop_mask   test_bishop_mask)
add_test(test_rook_mask     test_rook_mask)
