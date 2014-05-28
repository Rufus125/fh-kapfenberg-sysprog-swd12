#include <SDL/SDL.h>

#define DARK_RED        {139,0,0, 0}
#define LIGHT_GRAY      {211,211,211, 0}
#define DARK_MAGENTA    {139,0,139, 0}
#define DARK_BLUE       {0,0,139, 0}
#define DARK_GREEN      {0,100,0, 0}
#define DARK_BROWN      {92,64,51, 0}
#define DARK_CYAN       {0,139,139, 0}

enum Tetrimino_Type {
    I, J, L, O, S, T, Z
};

typedef struct {
    int x;
    int y;
    SDL_Color color;    
} Block;

typedef struct {
    Block blocks[4];
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


