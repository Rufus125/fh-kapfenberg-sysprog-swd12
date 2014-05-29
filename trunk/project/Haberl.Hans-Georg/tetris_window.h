#ifndef TETRIS_WINDOW
#define TETRIS_WINDOW
#include <SDL/SDL.h>

class Window {
    public:
    Window();
    ~Window();
    SDL_Event* getEvent();
    private:
    SDL_Event event;
};

#endif
