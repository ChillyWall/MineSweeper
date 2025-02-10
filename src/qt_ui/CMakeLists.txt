find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(
    MineSweeper-qt
    src/main.cpp
    src/mainwindow.cpp
    src/diff_menu.cpp
    src/cust_diff_form.cpp
    src/game_field.cpp
)
target_link_libraries(
    MineSweeper-qt
    PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets msutils
)
target_include_directories(MineSweeper-qt PRIVATE include)
