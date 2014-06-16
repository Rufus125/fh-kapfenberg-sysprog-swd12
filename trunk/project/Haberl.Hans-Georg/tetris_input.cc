#include "SDL/SDL.h"
#include "tetris_window.h"
#include "tetris_input.h"

Key Input::getKey() {
    if(SDL_PollEvent(this->event) && this->event->type == SDL_KEYDOWN) {
        SDLKey key = this->event->key.keysym.sym;
        
        switch(key) {
            case SDLK_ESCAPE:
                return ESC;
            case SDLK_LEFT:
                return LEFT;
            case SDLK_UP:
                return UP;
            case SDLK_RIGHT:
                return RIGHT;
            case SDLK_DOWN:
                return DOWN;
            case SDLK_SPACE:
                return SPACE;
            case SDLK_RETURN:
                return ENTER;
            default:
                return NONE;
        }   
    }
    return NONE;
}
