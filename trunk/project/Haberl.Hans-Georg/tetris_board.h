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
    //move tetrimino right
    void right();
    //move tetrimino down
    bool down();
    //rotate right
    void rotateRight();
    //drop tetrimino
    void drop();
    //speed up tetrimino
    void speedUp();
    //set drop speed
    void setDropInterval(int interval);
    //draw dirty fields
    void update();
    bool gameOver;
    long points;
    private:
    int offsetX;
    int offsetY;
    void drawTetrimino(Block* blocks, int x, int y, int color);
    Block* getCurrentBlocks();
    int* getCurrentBlockColor();
    void addTetrimino();
    void removeTetrimino();
    bool checkCollide(int dx, int dy);
    int getSingleBlockX(int idx);
    int getSingleBlockY(int idx);
    void newTetrimino();
    void drawBlock(int x, int y, int color);
    bool checkRow(int row);
    void deleteRow(int toDelete);

    typedef struct {
        Tetrimino* tetrimino;
        int pos_x;
        int pos_y;
    } CurrentBlock;

    SDL_Surface* window;
    bool dirty;
    int* oldColors[BOARD_BLOCKS_X][BOARD_BLOCKS_Y];
    CurrentBlock currentBlock;
    CurrentBlock nextBlock;
};

#endif
