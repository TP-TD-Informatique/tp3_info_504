cmake_minimum_required(VERSION 3.17)
project(tetris C)

set(CMAKE_C_STANDARD 99)

add_executable(tetris tetris.c gtktetris.c)

find_package(GTK2 2.6 REQUIRED gtk)

include_directories(${GTK2_INCLUDE_DIRS})
target_link_libraries(tetris ${GTK2_LIBRARIES})