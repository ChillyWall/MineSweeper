add_executable(MineSweeper src/main.cpp src/ui.cpp)
target_link_libraries(MineSweeper PRIVATE msutils)
target_include_directories(MineSweeper PRIVATE include)

install(TARGETS MineSweeper DESTINATION bin)
