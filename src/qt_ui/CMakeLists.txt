find_package(Qt6 COMPONENTS Core Gui Widgets Svg REQUIRED)

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

set(RUNTIME_LIBS Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Svg)

set(RESOURCES resources.qrc)

add_executable(MineSweeper-qt ${SOURCES} ${HEADERS} ${RESOURCES})
target_link_libraries(MineSweeper-qt PRIVATE msutils ${RUNTIME_LIBS})
target_include_directories(MineSweeper-qt PRIVATE include)

install(TARGETS MineSweeper-qt DESTINATION bin)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    # # fill in the path to your Qt installation, like C:/Qt/6.8.1/mingw_64
    # set(QT_INSTALL_PATH "")
    # install(
    #     FILES ${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll
    #     DESTINATION bin/plugins/platforms
    # )
    # install(
    #     FILES ${QT_INSTALL_PATH}/plugins/iconengines/qsvgicon.dll
    #     DESTINATION bin/plugins/iconengines
    # )
    set_target_properties(MineSweeper-qt PROPERTIES WIN32_EXECUTABLE TRUE)
    install(IMPORTED_RUNTIME_ARTIFACTS ${RUNTIME_LIBS} DESTINATION bin)
endif()
