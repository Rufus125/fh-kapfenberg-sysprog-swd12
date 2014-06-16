#include "tetris_colors.h"
#include "tetris_blocks.h"
#include "tetris_tetrimino.h"
#include <cstdlib>
#include <ctime>

class TetriminoDouble : public Tetrimino {
    void right() {
        this->facing ^= 1;
    }
    void left() {
        this->facing ^= 1;
    }
};
class TetriminoQuatrouple : public Tetrimino {
    void right() {
        this->facing = ++this->facing%4;
    }
    void left() {
        this->facing = (this->facing+3)%4;
    }
};

class I_Tetrimino : public TetriminoDouble {
    TetriminoBlocks getBlocks() {
        return I_BLOCKS[this->facing];
    }
};

class J_Tetrimino : public TetriminoQuatrouple {
    TetriminoBlocks getBlocks() {
        return J_BLOCKS[this->facing];
    }
};

class L_Tetrimino : public TetriminoQuatrouple {
    TetriminoBlocks getBlocks() {
        return L_BLOCKS[this->facing];
    }
};

class O_Tetrimino : public Tetrimino {
    TetriminoBlocks getBlocks() {
        return O_BLOCKS;
    }
    void right() {
    }
    void left() {
    }
};

class S_Tetrimino : public TetriminoDouble {
    TetriminoBlocks getBlocks() {
        return S_BLOCKS[this->facing];
    }
};

class T_Tetrimino : public TetriminoQuatrouple {
    TetriminoBlocks getBlocks() {
        return T_BLOCKS[this->facing];
    }
};

class Z_Tetrimino : public TetriminoDouble {
    TetriminoBlocks getBlocks() {
        return Z_BLOCKS[this->facing];
    }
};


Tetrimino* createTetrimino(Tetrimino_Type type) {
    switch(type) {
        case I:
            return new I_Tetrimino();
        case J:
            return new J_Tetrimino();
        case L:
            return new L_Tetrimino();
        case O:
            return new O_Tetrimino();
        case S:
            return new S_Tetrimino();
        case T:
            return new T_Tetrimino();
        case Z:
            return new Z_Tetrimino();
    }
}

static long additionalForMS = 0;
Tetrimino* createRandomTetrimino() {
    srand(time(NULL) + (additionalForMS++));
    Tetrimino_Type type = static_cast<Tetrimino_Type>(rand() % Z);
    return createTetrimino(type);
}

void setColorStyle(Tetris_Color_Style style) {
    switch(style) {
        case MICROSOFT:
            color_I = RED;
            color_J = MAGENTA;
            color_L = YELLOW;
            color_O = CYAN;
            color_S = BLUE;
            color_T = LIGHT_GRAY;
            color_Z = LIME;
            return;
        case SEGA:
            color_I = RED;
            color_J = BLUE;
            color_L = ORANGE;
            color_O = YELLOW;
            color_S = MAGENTA;
            color_T = CYAN;
            color_Z = LIME;
            return;
        case THE_NEW_TETRIS:
            color_I = CYAN;
            color_J = BLUE_MAGENTA;
            color_L = MAGENTA;
            color_O = LIGHT_GRAY;
            color_S = LIME;
            color_T = YELLOW;
            color_Z = RED;
            return;
        case THE_TETRIS_COMPANY:
            color_I = CYAN;
            color_J = BLUE;
            color_L = ORANGE;
            color_O = YELLOW;
            color_S = LIME;
            color_T = DARK_MAGENTA;
            color_Z = RED;
            return;
        case ATARI:
            color_I = RED;
            color_J = YELLOW;
            color_L = MAGENTA;
            color_O = BLUE;
            color_S = CYAN;
            color_T = LIME;
            color_Z = ORANGE;
            return;
        case TETRIS_THE_SOVIET_MIND_GAME:
            color_I = RED;
            color_J = ORANGE;
            color_L = MAGENTA;
            color_O = BLUE;
            color_S = LIME;
            color_T = OLIVE;
            color_Z = CYAN;
            return;
        case GAMEBOY_COLOR:
            color_I = ORANGE;
            color_J = CYAN;
            color_L = RED;
            color_O = YELLOW;
            color_S = MAGENTA;
            color_T = LIME;
            color_Z = AMBER;
        case VADIM_GERASIMOV:
        default:
            color_I = DARK_RED;
            color_J = LIGHT_GRAY;
            color_L = DARK_MAGENTA;
            color_O = DARK_BLUE;
            color_S = DARK_GREEN;
            color_T = DARK_BROWN;
            color_Z = DARK_CYAN;
            return;
    }

}
