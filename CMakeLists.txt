project(CPP-PROJECT)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

set(ASAN_COMPILE_FLAGS -fsanitize=address,undefined -fno-sanitize-recover=all -g)
set(ASAN_LINK_FLAGS -fsanitize=address,undefined)

add_compile_options(${ASAN_COMPILE_FLAGS})
add_link_options(${ASAN_LINK_FLAGS})

add_compile_options(-Wall -Wextra -pedantic -g)

add_subdirectory(term-2)
