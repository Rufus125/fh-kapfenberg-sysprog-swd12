

enum Key {
    LEFT, UP, RIGHT, DOWN, SPACE, ENTER, ESC, NONE, PAUSE
};

class Input {
    public:
    Input(SDL_Event*_event) : event(_event) {};
    Key getKey();
    private:
    SDL_Event* event;
};
