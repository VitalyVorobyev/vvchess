
add_compile_options(-O2 -g -no-pie)
# add_compile_options(-O3)

add_executable(vvchess
    definitions.cpp
    magicfinder.cpp
    main.cpp
)
