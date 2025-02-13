find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(fmt REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/diff_menu.cpp
    src/cust_diff_form.cpp
    src/game_field.cpp
)

set(HEADERS
    include/mainwindow.hpp
    include/diff_menu.hpp
    include/cust_diff_form.hpp
    include/game_field.hpp
)

set(RESOURCES resources.qrc)

add_executable(MineSweeper-qt ${SOURCES} ${HEADERS} ${RESOURCES})
target_link_libraries(
    MineSweeper-qt
    PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets msutils fmt::fmt
)
qt6_add_resources(MineSweeper-qt resources.qrc)
target_include_directories(MineSweeper-qt PRIVATE include)

install(TARGETS MineSweeper-qt DESTINATION bin)
