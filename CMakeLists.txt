cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_FLAGS_DEBUG "-g -O0")

project(LeXa)

add_executable(
    lx
    "${CMAKE_CURRENT_LIST_DIR}/src/lexa.c"
)

target_include_directories(
    lx
    PUBLIC
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/include"
)
