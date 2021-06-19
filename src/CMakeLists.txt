
# add_compile_options(-O2 -g -no-pie)
add_compile_options(-O2)

add_executable(findmagic
    definitions.cpp
    bbtools.cpp
    magicfinder.cpp
    run_magicfinder.cpp
)

add_compile_options(-O0)

add_executable(main
    definitions.cpp
    bbtools.cpp
    attacks.cpp
    main.cpp
)
