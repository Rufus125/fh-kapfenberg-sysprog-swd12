#ifndef TETRIS_COLORS
#define TETRIS_COLORS
#include "SDL/SDL.h"

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    static Uint32 rmask = 0xff000000;
    static Uint32 gmask = 0x00ff0000;
    static Uint32 bmask = 0x0000ff00;
    static Uint32 amask = 0x000000ff;
#else
    static Uint32 rmask = 0x000000ff;
    static Uint32 gmask = 0x0000ff00;
    static Uint32 bmask = 0x00ff0000;
    static Uint32 amask = 0xff000000;
#endif

static const int WHITE          = 0xFFFFFF;
static const int RED            = 0xFF0000;
static const int DARK_RED       = 0x8B0000;
static const int LIGHT_GRAY     = 0xD3D3D3;
static const int MAGENTA        = 0xFF00FF;
static const int DARK_MAGENTA   = 0x8B008B;
static const int BLUE           = 0x0000FF;
static const int DARK_BLUE      = 0x00008B;
static const int DARK_GREEN     = 0x008B00;
static const int DARK_BROWN     = 0x5C4033;
static const int CYAN           = 0x00FFFF;
static const int DARK_CYAN      = 0x008B8B;
static const int YELLOW         = 0xFFFF00;
static const int LIME           = 0x00FF00;
static const int ORANGE         = 0xFFA500;
static const int BLUE_MAGENTA   = 0x8000FF;
static const int OLIVE          = 0x808000;
static const int AMBER          = 0xFFC000;
static const int BLACK          = 0x000000;
#endif
