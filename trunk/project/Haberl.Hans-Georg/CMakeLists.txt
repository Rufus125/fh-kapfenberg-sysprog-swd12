cmake_minimum_required(VERSION 2.8)
Project(tetris)

FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(SDL_image REQUIRED)

LINK_LIBRARIES(
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
)

ADD_EXECUTABLE(
    tetris
    tetris.cc
    tetris_window.cc
    tetris_blocks.cc
    tetris_board.cc
    tetris_input.cc
)
