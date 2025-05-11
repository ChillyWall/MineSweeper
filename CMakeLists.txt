cmake_minimum_required(VERSION 3.31)
project(MineSweeper LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/msutils)
add_subdirectory(src/ui)
add_subdirectory(src/qt_ui)
