#include <SDL/SDL.h> 

static const TetriminoBlocks I_BLOCKS[2] = {
    {{
        {0,1},  {1,1},  {2,1},  {3,1}
    }, &color_I},
    {{
                {1,0},
                {1,1},
                {1,2},
                {1,3}
    }, &color_I}

};
static const TetriminoBlocks J_BLOCKS[4] = {
    {{
        {0,1},  {1,1},  {2,1},
                        {2,2}
    }, &color_J},
    {{
                {1,0},
                {1,1},
        {0,2},  {1,2}
    }, &color_J},
    {{
        {0,0},
        {0,1},  {1,1},  {2,1}
    }, &color_J},
    {{
                {1,0},
                {1,1},
        {0,2},  {1,2}
    }, &color_J}
};
static const TetriminoBlocks L_BLOCKS[4] = {
    {{
        {0,1},  {1,1},  {2,1},
        {0,2}
    }, &color_Z},
    {{
                {1,0},
                {1,1},
                {1,2},  {2,2}
    }, &color_Z},
    {{
                        {2,0},
        {0,1},  {1,1},  {2,1}
    }, &color_Z},
    {{
                {1,0},
                {1,1},
                {1,2}, {2,2}
    }, &color_Z}
};
static const TetriminoBlocks O_BLOCKS = {{
        {1,2},  {2,2},
        {1,3},  {2,3}
}, &color_O};
static const TetriminoBlocks S_BLOCKS[2] = {
    {{
                {1,0},  {2,0},
        {0,1},  {1,1}
    }, &color_S},
    {{
        {0,0}, 
        {0,1},  {1,1}, 
                {1,2}
    }, &color_S}
};
static const TetriminoBlocks T_BLOCKS[4] = {
    {{
        {0,0}, {1,0}, {2,0},
                        {1,1}
    }, &color_T},
    {{
                        {1,0}, 
        {0,1}, {1,1},
                        {1,2}
    }, &color_T},
    {{
                        {1,0},
        {0,1}, {1,1}, {2,1},
    }, &color_T},
    {{
                        {1,0}, 
                        {1,1}, {2,1},
                        {1,2}
    }, &color_T}
};
static const TetriminoBlocks Z_BLOCKS[2] = {
    {{
        {0,0}, {1,0},
                        {1,1}, {2,1}
    }, &color_Z},
    {{
                                        {2,0}, 
                        {1,1}, {2,1}, 
                        {1,2}
    }, &color_Z}
};
