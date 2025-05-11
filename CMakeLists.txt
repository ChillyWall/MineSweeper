cmake_minimum_required(VERSION 3.16)
project(
    MineSweeper
    VERSION 1.0
    DESCRIPTION "A MineSweeper game written in C++ with Qt6"
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src/msutils)
add_subdirectory(src/ui)
add_subdirectory(src/qt_ui)
