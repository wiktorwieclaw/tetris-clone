cmake_minimum_required(VERSION 3.17)
project(tetris-clone)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
add_subdirectory(lib)