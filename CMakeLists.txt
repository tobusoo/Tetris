cmake_minimum_required(VERSION 3.22)

project(
    Tetris
    VERSION 1.0
    LANGUAGES CXX   
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

add_subdirectory(src)
include_directories(${CMAKE_SOURCE_DIR}/include)