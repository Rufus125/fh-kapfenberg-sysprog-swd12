#ifndef TETRIS_BLOCKS
#define TETRIS_BLOCKS
#include <SDL/SDL.h>
#include "tetris_colors.h"
#include "tetris.h"

//default color style VADIM_GERASIMOV
static int color_I = DARK_RED;
static int color_J = LIGHT_GRAY;
static int color_L = DARK_MAGENTA;
static int color_O = DARK_BLUE;
static int color_S = DARK_GREEN;
static int color_T = DARK_BROWN;
static int color_Z = DARK_CYAN;

enum Tetris_Color_Style {
    VADIM_GERASIMOV,
    MICROSOFT,
    SEGA,
    THE_NEW_TETRIS,
    THE_TETRIS_COMPANY,
    ATARI,
    TETRIS_THE_SOVIET_MIND_GAME,
    GAMEBOY_COLOR
};

enum Tetrimino_Type {
    I, J, L, O, S, T, Z
};

typedef struct {
    int x;
    int y;
} Block;

typedef struct {
    Block blocks[TETRIMINO_BLOCK_NUM];
    int* color;    
} TetriminoBlocks;

class Tetrimino {
    protected:
    int facing;
    public:
        Tetrimino(): facing(0) {}
        virtual TetriminoBlocks getBlocks()=0;
        virtual void left()=0;
        virtual void right()=0;
};

Tetrimino* createTetrimino(Tetrimino_Type type);
Tetrimino* createRandomTetrimino();

void setColorStyle(Tetris_Color_Style style);
#endif
