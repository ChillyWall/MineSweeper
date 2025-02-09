add_executable(MineSweeper src/main.cpp src/ui.cpp)
target_link_libraries(MineSweeper PUBLIC msutils)
target_include_directories(MineSweeper PUBLIC include)

install(TARGETS MineSweeper DESTINATION bin)
