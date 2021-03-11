cmake_minimum_required(VERSION 3.12)
project(Amazones)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
link_directories(bin)
link_directories(lib)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "include/amazones/*.h"
        )

file(GLOB_RECURSE TEST_SOURCE_FILES
        "test/*.cpp"
        "src/amazones/*.cpp"
        "include/*.h"
        )

add_executable(Amazones ${SOURCE_FILES})

add_executable(AmazonesTests ${TEST_SOURCE_FILES})

target_link_libraries(Amazones SDL SDL_image SDL_mixer SDL_ttf)
