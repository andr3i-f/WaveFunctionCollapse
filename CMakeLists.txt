cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(wfc)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY  https://github.com/SFML/SFML.git
        GIT_TAG origin/master
)

FetchContent_MakeAvailable(SFML)

add_executable(wfc
        src/main.cpp
        src/world.cpp
        src/world.hpp
        src/tile.cpp
        src/tile.hpp
)

target_link_libraries(wfc PRIVATE sfml-graphics)