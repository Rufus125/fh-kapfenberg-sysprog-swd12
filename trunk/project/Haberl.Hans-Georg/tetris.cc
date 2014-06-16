#include "tetris.h"
#include "tetris_window.h"
#include "tetris_blocks.h"
#include "tetris_board.h"
#include "tetris_input.h"
#include <iostream>

int main(int argc, char **argv) {
    Window* window = new Window();
    Input* input = new Input(window->getEvent());
    Board* board = new Board(window->getScreen(), BOARD_OFFSET_X, BOARD_OFFSET_Y); 

    bool running = true;
    do {
        Key key = input->getKey();
        if(key == ESC) running = false;
        if(key == LEFT) {
            board->left();
        }

        board->update();
    } while (running);

    delete (board);
    delete (input);
    delete (window);
    
    return(0);
}

