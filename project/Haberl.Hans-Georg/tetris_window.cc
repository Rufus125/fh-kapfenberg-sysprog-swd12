#include "tetris_window.h"

const int HEIGHT = 640;
const int WIDTH = 480;
const char* TITLE = "Tetris - Hans-Georg Haberl - SWD12";

Window* Window::Instance() {
    static Window instance;
    return &instance;
}

Window::Window() {
    //setting up SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(TITLE, 0);
    //todo background
    
    this->event = event;
}

SDL_Event Window::getEvent() {
    return this->event;
}

Window::~Window() {
    SDL_Quit();
}
