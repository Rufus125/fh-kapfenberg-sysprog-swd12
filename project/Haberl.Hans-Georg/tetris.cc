#include "tetris_window.h"
#include "tetris_blocks.h"
#include "tetris_input.h"
#include <iostream>

void printtt(TetriminoBlocks tetriminoBlocks);
int main(int argc, char **argv) {
    Window* window = new Window();
    Input* input = new Input(window->getEvent());

    bool running = true;
    do {
        Key key = input->getKey();
        if(key == ESC) running = false;
    } while (running);

    delete (input);
    delete (window);
    
    return(0);
}

