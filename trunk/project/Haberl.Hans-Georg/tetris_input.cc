#include "SDL/SDL.h"
#include "tetris_window.h"
#include "tetris_input.h"

Key Input::getKey() {
    if(SDL_PollEvent(this->event) && this->event->type == SDL_KEYDOWN) {
        SDLKey key = this->event->key.keysym.sym;
        
        switch(key) {
        case SDLK_ESCAPE:
            return ESC;
        }

    }
    return NONE;
}
