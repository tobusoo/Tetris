cmake_minimum_required(VERSION 3.10)

project(tetris VERSION 0.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(FLAGS "-Wall -g -I include")
add_definitions(${FLAGS})

add_executable(tetris src/main.cpp)

add_custom_target(copy-files ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/resource
    ${PROJECT_BINARY_DIR}/resource
    COMMENT "COPY RESOURCE FILES"
)

add_dependencies(tetris copy-files)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(tetris sfml-graphics sfml-audio)