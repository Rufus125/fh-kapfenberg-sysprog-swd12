#ifndef TETRIS_BOARD
#define TETRIS_BOARD
#include <SDL/SDL.h>
#include "tetris.h"
#include "tetris_blocks.h"
#include <vector>

class Board {
    public:
    Board(SDL_Surface *screen, int offsetX, int offsetY);
    ~Board();
    //move tetrimino left
    void left();
    //move tetrimino down
    void right();
    //drop tetrimino
    void drop();
    //speed up tetrimino
    void speedUp();
    //set drop speed
    void setDropInterval(int interval);
    //draw dirty fields
    void update();
    private:
    int offsetX;
    int offsetY;
    void drawTetrimino(Block* blocks, int x, int y, int color);
    Block* getCurrentBlocks();
    int getCurrentBlockColor();

    typedef struct {
        Tetrimino* tetrimino;
        int pos_x;
        int pos_y;
    } CurrentBlock;

    SDL_Surface* window;
    bool dirty;
    const int* oldColors[BOARD_BLOCKS_X][BOARD_BLOCKS_Y];
    const int* newColors[BOARD_BLOCKS_X][BOARD_BLOCKS_Y];
    //bool blocked[BOARD_BLOCKS_X][BOARD_BLOCKS_Y];
    CurrentBlock currentBlock;
};

#endif
