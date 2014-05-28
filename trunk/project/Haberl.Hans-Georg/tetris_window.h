#ifndef TETRIS_WINDOW
#define TETRIS_WINDOW
#include <SDL/SDL.h>

class Window {
    public:
    static Window* Instance(); 
    ~Window();
    SDL_Event getEvent();
    private:
    Window();
    SDL_Event event;
};

#endif
