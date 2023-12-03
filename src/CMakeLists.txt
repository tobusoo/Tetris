set(target_name tetris)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
    ${target_name}
    PRIVATE
    main.cpp
    BricksGenerator.cpp
    NextBrickPanel.cpp
    StatisticPanel.cpp
    TextEffect.cpp
    DropEffect.cpp
    bricks/Brick.cpp
    bricks/DrawableBrick.cpp
    bricks/GhostBrick.cpp
    bricks/IBrick.cpp
    bricks/JBrick.cpp
    bricks/LBrick.cpp
    bricks/OBrick.cpp
    bricks/SBrick.cpp
    bricks/TBrick.cpp
    bricks/ZBrick.cpp
    Field.cpp
)

find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

target_link_libraries(
  ${target_name}
  PRIVATE
    sfml-graphics
    sfml-system
    sfml-window
)

include_directories(${CMAKE_SOURCE_DIR}/include)
