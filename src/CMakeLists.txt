cmake_minimum_required(VERSION 3.3)

file(GLOB HEADERS
  "${PROJECT_SOURCE_DIR}/header/*.h"
)

file(GLOB SRC
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(et ${SRC} ${HEADERS})
