cmake_minimum_required(VERSION 3.1)

set(CMAKE_USE_RELATIVE_PATHS TRUE)

file(GLOB SRC
    "*.cpp"
    "./header/*.h"
    "./src/*.cpp"
)

add_executable(Editor_Texto ${SRC})
