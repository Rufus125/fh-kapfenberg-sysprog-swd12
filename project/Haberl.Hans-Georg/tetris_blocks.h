#include <SDL/SDL.h>


static const SDL_Color RED          = {255,  0,  0,  0};
static const SDL_Color DARK_RED     = {139,  0,  0,  0};
static const SDL_Color LIGHT_GRAY   = {211,211,211,  0};
static const SDL_Color MAGENTA      = {255,  0,255,  0};
static const SDL_Color DARK_MAGENTA = {139,  0,139,  0};
static const SDL_Color BLUE         = {  0,  0,255,  0};
static const SDL_Color DARK_BLUE    = {  0,  0,139,  0};
static const SDL_Color DARK_GREEN   = {  0,100,  0,  0};
static const SDL_Color DARK_BROWN   = { 92, 64, 51,  0};
static const SDL_Color CYAN         = {  0,255,255,  0};
static const SDL_Color DARK_CYAN    = {  0,139,139,  0};
static const SDL_Color YELLOW       = {255,255,  0,  0};
static const SDL_Color LIME         = {  0,255,  0,  0};
static const SDL_Color ORANGE       = {255,165,  0,  0};
static const SDL_Color BLUE_MAGENTA = {128,  0,255,  0};
static const SDL_Color OLIVE        = {128,128,  0,  0};
static const SDL_Color AMBER        = {255,192,  0,  0};

//default color style VADIM_GERASIMOV
static SDL_Color color_I = DARK_RED;
static SDL_Color color_J = LIGHT_GRAY;
static SDL_Color color_L = DARK_MAGENTA;
static SDL_Color color_O = DARK_BLUE;
static SDL_Color color_S = DARK_GREEN;
static SDL_Color color_T = DARK_BROWN;
static SDL_Color color_Z = DARK_CYAN;

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
    SDL_Color* color;    
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

void setColorStyle(Tetris_Color_Style style);
