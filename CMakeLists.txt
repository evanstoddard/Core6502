cmake_minimum_required(VERSION 3.7)

project(Core6502)

set(PROJECT_BINARY_DIR ${CMAKE_BINARY_DIR}/build)
set (CMAKE_CXX_STANDARD 11)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)