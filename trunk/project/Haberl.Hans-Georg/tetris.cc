#include "tetris.h"
#include "tetris_window.h"
#include "tetris_blocks.h"
#include "tetris_board.h"
#include "tetris_input.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
    Window* window = new Window();
    Input* input = new Input(window->getEvent());
    Board* board = new Board(window->getScreen(), BOARD_OFFSET_X, BOARD_OFFSET_Y); 
    int down = 0;
    BOARD_COLOR = (int *) &BLACK;

    bool running = true;
    do {
        Key key = input->getKey();
        if(key == PAUSE) {
            Key key2;
            do {
                key2 = input->getKey();
                if(key2==ESC) {
                    running = false;
                    break;
                }
            } while(key2 != PAUSE);
        }
        if(key == ESC) running = false;
        if(!running) break;
        if(key == LEFT) {
            board->left();
        }
        if(key == RIGHT) {
            board->right();
        }
        if(key == DOWN) {
            board->down();
        }
        if(key == UP) {
            board->rotateRight();
        }
        if(key == SPACE) {
            board->drop();
        }

        if(board->gameOver) {
            break;
        }

        board->update();

        usleep(1000);
        if(down++>100) {
            down = 0;
            board->down();
            if(board->gameOver) {
                break;
            }
        }
        
    } while (running);

    std::cout<<"POINTS:" << board->points << "\n";
    delete (board);
    delete (input);
    delete (window);
    
    return(0);
}

