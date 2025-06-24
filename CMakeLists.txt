cmake_minimum_required(VERSION 3.26)
project(ListForAll C)
project(example)

set(CMAKE_C_STANDARD 11)

add_library(ListForAll library.c)

add_executable(example example.c)
target_link_libraries(example ListForAll)
