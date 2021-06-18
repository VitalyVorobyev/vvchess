
add_compile_options(-O2 -g -no-pie)
# add_compile_options(-O3)

add_executable(findmagic
    definitions.cpp
    magicfinder.cpp
    attacks.cpp
    run_magicfinder.cpp
)
