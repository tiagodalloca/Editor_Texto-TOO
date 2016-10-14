cmake_minimum_required(VERSION 3.3)

include_directories (
  "${PROJECT_SOURCE_DIR}/header/"
)

#[[file(GLOB HEADERS
  "${PROJECT_SOURCE_DIR}/header/*.h"
)

file(GLOB SRC
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
)]]

set (HEADERS
  ${PROJECT_SOURCE_DIR}/header/ListaSimples.h
  ${PROJECT_SOURCE_DIR}/header/String.h
)

set (SRC
  String.cpp
)

set (ALL ${HEADERS} ${SRC})

add_library(lib
${ALL})

foreach (FILE ${ALL})
  message (${FILE}) 
endforeach (FILE)

add_executable(et main.cpp)
target_link_libraries(et lib)
