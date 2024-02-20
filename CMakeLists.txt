cmake_minimum_required(VERSION 3.27)
project(lett C)

set(CMAKE_C_STANDARD 99)

add_executable(lett
        src/main.c
        src/lett.h
        src/lt_chunk.c
        src/lt_chunk.h
        src/lt_memory.c
        src/lt_memory.h
        src/lt_vm.c
        src/lt_vm.h
        src/lt_lexer.c
        src/lt_lexer.h
        src/lt_value.c
        src/lt_value.h
        src/lt_collections.c
        src/lt_collections.h
        src/lt_common.h)

target_compile_options(lett PRIVATE -Wall -Wextra -Wpedantic -Werror)
