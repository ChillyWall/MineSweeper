find_package(
    SFML
    COMPONENTS graphics system audio window network
    REQUIRED
)

add_executable(main src/main.cpp)
target_link_libraries(
    main
    PRIVATE sfml-graphics sfml-system sfml-audio sfml-window sfml-network
)
