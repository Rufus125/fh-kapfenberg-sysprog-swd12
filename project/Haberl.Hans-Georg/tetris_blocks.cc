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

Tetrimino* createRandomTetrimino() {
    srand(time(NULL));
    Tetrimino_Type type = static_cast<Tetrimino_Type>(rand() % Z);
    return createTetrimino(type);
}
