include_directories ("${CMAKE_SOURCE_DIR}/header")

#[[file(GLOB SRC
  *.cpp
)
add_library(src ${SRC})]]
add_executable(et main.cpp)
#xtarget_link_libraries(et src)
