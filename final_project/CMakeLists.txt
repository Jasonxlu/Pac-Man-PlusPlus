cmake_minimum_required(VERSION 3.3)

# TODO: Change “game” to the name of your game (no spaces!):
set(GAME_EXE Pac-Man++)

project(${GAME_EXE} CXX)
include(.cs211/cmake/CMakeLists.txt)

# TODO: PUT ADDITIONAL MODEL .cxx FILES IN THIS LIST:
set(MODEL_SRC
        src/model.cxx
        src/maze.cxx
        src/pacman.cxx
        src/ghost.cxx
        src/character.cxx
        src/position_set.cxx
        src/tile.cxx)

# TODO: PUT ADDITIONAL NON-MODEL (UI) .cxx FILES IN THIS LIST:
add_program(${GAME_EXE}
        src/view.cxx
        src/controller.cxx
        src/main.cxx
        ${MODEL_SRC})
target_link_libraries(${GAME_EXE} ge211)

add_test_program(model_test
        test/model_test.cxx
        ${MODEL_SRC})
target_link_libraries(model_test ge211)

# vim: ft=cmake
