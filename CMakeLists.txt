cmake_minimum_required(VERSION 3.27)
project(lett C)

set(CMAKE_C_STANDARD 99)

add_executable(lett src/main.c)

target_compile_options(lett PRIVATE -Wall -Wextra -Wpedantic -Werror)
