cmake_minimum_required(VERSION 3.25)

set(CMAKE_C_FLAGS_DEBUG "-g -O0")

project(LeXa)

add_executable(lx "${CMAKE_SOURCE_DIR}/src/lexer.c")
target_include_directories(lexa PUBLIC "${CMAKE_SOURCE_DIR}")
