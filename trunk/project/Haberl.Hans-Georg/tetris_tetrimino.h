#include <SDL/SDL.h> 

static const TetriminoBlocks I_BLOCKS[2] = {
    {{
        {0,1,DARK_RED}, {1,1,DARK_RED}, {2,1,DARK_RED}, {3,1,DARK_RED}
    }},
    {{
        {1,0,DARK_RED},
        {1,1,DARK_RED},
        {1,2,DARK_RED},
        {1,3,DARK_RED}
    }}

};
static const TetriminoBlocks J_BLOCKS[4] = {
    {{
        {0,1,LIGHT_GRAY}, {1,1,LIGHT_GRAY}, {2,1,LIGHT_GRAY},
                                            {2,2,LIGHT_GRAY}
    }},
    {{
                          {1,0,LIGHT_GRAY},
                          {1,1,LIGHT_GRAY},
        {0,2,LIGHT_GRAY}, {1,2,LIGHT_GRAY}
    }},
    {{
        {0,0,LIGHT_GRAY},
        {0,1,LIGHT_GRAY}, {1,1,LIGHT_GRAY}, {2,1,LIGHT_GRAY}
    }},
    {{
                          {1,0,LIGHT_GRAY},
                          {1,1,LIGHT_GRAY},
        {0,2,LIGHT_GRAY}, {1,2,LIGHT_GRAY}
    }}
};
static const TetriminoBlocks L_BLOCKS[4] = {
    {{
        {0,1,DARK_MAGENTA}, {1,1,DARK_MAGENTA}, {2,1,DARK_MAGENTA},
        {0,2,DARK_MAGENTA}
    }},
    {{
                            {1,0,DARK_MAGENTA},
                            {1,1,DARK_MAGENTA},
                            {1,2,DARK_MAGENTA}, {2,2,DARK_MAGENTA}
    }},
    {{
                                                {2,0,DARK_MAGENTA},
        {0,1,DARK_MAGENTA}, {1,1,DARK_MAGENTA}, {2,1,DARK_MAGENTA}
    }},
    {{
                            {1,0,DARK_MAGENTA},
                            {1,1,DARK_MAGENTA},
                            {1,2,DARK_MAGENTA}, {2,2,DARK_MAGENTA}
    }}
};
static const TetriminoBlocks O_BLOCKS = {{
    {0,0,DARK_BLUE}, {1,0,DARK_BLUE},
    {0,1,DARK_BLUE}, {1,1,DARK_BLUE}
}};
static const TetriminoBlocks S_BLOCKS[2] = {
    {{
                          {1,0,DARK_GREEN}, {2,0,DARK_GREEN},
        {0,1,DARK_GREEN}, {1,1,DARK_GREEN}
    }},
    {{
        {0,0,DARK_GREEN}, 
        {0,1,DARK_GREEN}, {1,1,DARK_GREEN}, 
                          {1,2,DARK_GREEN}
    }}
};
static const TetriminoBlocks T_BLOCKS[4] = {
    {{
        {0,0,DARK_BROWN}, {1,0,DARK_BROWN}, {2,0,DARK_BROWN},
                          {1,1,DARK_BROWN}
    }},
    {{
                          {1,0,DARK_BROWN}, 
        {0,1,DARK_BROWN}, {1,1,DARK_BROWN},
                          {1,2,DARK_BROWN}
    }},
    {{
                          {1,0,DARK_BROWN},
        {0,1,DARK_BROWN}, {1,1,DARK_BROWN}, {2,1,DARK_BROWN},
    }},
    {{
                          {1,0,DARK_BROWN}, 
                          {1,1,DARK_BROWN}, {2,1,DARK_BROWN},
                          {1,2,DARK_BROWN}
    }}
};
static const TetriminoBlocks Z_BLOCKS[2] = {
    {{
        {0,0,DARK_MAGENTA}, {1,0,DARK_MAGENTA},
                            {1,1,DARK_MAGENTA}, {2,1,DARK_MAGENTA}
    }},
    {{
                                                {2,0,DARK_MAGENTA}, 
                            {1,1,DARK_MAGENTA}, {2,1,DARK_MAGENTA}, 
                            {1,2,DARK_MAGENTA}
    }}
};
