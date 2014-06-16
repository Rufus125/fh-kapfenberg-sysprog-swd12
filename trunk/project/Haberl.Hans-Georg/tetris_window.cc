#include "tetris_window.h"

const int HEIGHT = 480;
const int WIDTH = 640;
const char* TITLE = "Tetris - Hans-Georg Haberl - SWD12";

Window::Window() {
    //setting up SDL
    SDL_Init(SDL_INIT_VIDEO);
    this->screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(TITLE, 0);
    
    this->event = event;
}

SDL_Surface* Window::getScreen() {
    return this->screen;
}

SDL_Event* Window::getEvent() {
    return &this->event;
}

Window::~Window() {
    SDL_Quit();
}
