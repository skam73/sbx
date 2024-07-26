cmake_minimum_required(VERSION 3.18)
project(
    snake
    VERSION 0.0.0
    DESCRIPTION "HW 08 Snake"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

set(sources
    src/snake.h
    src/snake.cpp
    src/main.cpp
)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(snake ${sources})

target_link_libraries(snake PRIVATE Qt5::Core Qt5::Widgets ${LINK_FLAGS})