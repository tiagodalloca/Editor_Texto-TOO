cmake_minimum_required(VERSION 3.3)

project(Editor CXX C)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories (
  header/
  src/
  include/
)

set (HEADERS
  header/ListaSimples.h
  header/ListaCD.h
  header/MyString.h
  header/Pilha.h

  header/Buffer.h
  header/KeyResolver.h
  header/Misc.h
)

set (SRC
  src/MyString.cpp
  src/Buffer.cpp
  src/KeyResolver.cpp
)

set (ALL ${HEADERS} ${SRC})

add_library(lib
${ALL})

foreach (FILE ${ALL})
  message (${FILE}) 
endforeach (FILE)

add_executable(et src/main.cpp include/conio.o)
target_link_libraries(et lib)
