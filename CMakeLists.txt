cmake_minimum_required(VERSION 3.3)

project(Editor CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories (
  header/
  src/
)

set (HEADERS
  header/ListaSimples.h
  header/String.h
  header/Pilha.h
)

set (SRC
  src/String.cpp
)

set (ALL ${HEADERS} ${SRC})

add_library(lib
${ALL})

foreach (FILE ${ALL})
  message (${FILE}) 
endforeach (FILE)

add_executable(et src/main.cpp)
target_link_libraries(et lib)
