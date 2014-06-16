#ifndef TETRIS_WINDOW
#define TETRIS_WINDOW
#include <SDL/SDL.h>

class Window {
    public:
    Window();
    ~Window();
    SDL_Surface* getScreen();
    SDL_Event* getEvent();
    private:
    SDL_Surface* screen;
    SDL_Event event;
};

#endif
