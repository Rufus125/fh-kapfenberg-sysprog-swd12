#include <SDL/SDL.h> 

static const TetriminoBlocks I_BLOCKS[2] = {
    {{
        {0,1,&color_I}, {1,1,&color_I}, {2,1,&color_I}, {3,1,&color_I}
    }},
    {{
        {1,0,&color_I},
        {1,1,&color_I},
        {1,2,&color_I},
        {1,3,&color_I}
    }}

};
static const TetriminoBlocks J_BLOCKS[4] = {
    {{
        {0,1,&color_J}, {1,1,&color_J}, {2,1,&color_J},
                                        {2,2,&color_J}
    }},
    {{
                        {1,0,&color_J},
                        {1,1,&color_J},
        {0,2,&color_J}, {1,2,&color_J}
    }},
    {{
        {0,0,&color_J},
        {0,1,&color_J}, {1,1,&color_J}, {2,1,&color_J}
    }},
    {{
                        {1,0,&color_J},
                        {1,1,&color_J},
        {0,2,&color_J}, {1,2,&color_J}
    }}
};
static const TetriminoBlocks L_BLOCKS[4] = {
    {{
        {0,1,&color_Z}, {1,1,&color_Z}, {2,1,&color_Z},
        {0,2,&color_Z}
    }},
    {{
                        {1,0,&color_Z},
                        {1,1,&color_Z},
                        {1,2,&color_Z}, {2,2,&color_Z}
    }},
    {{
                                        {2,0,&color_Z},
        {0,1,&color_Z}, {1,1,&color_Z}, {2,1,&color_Z}
    }},
    {{
                        {1,0,&color_Z},
                        {1,1,&color_Z},
                        {1,2,&color_Z}, {2,2,&color_Z}
    }}
};
static const TetriminoBlocks O_BLOCKS = {{
        {0,0,&color_O}, {1,0,&color_O},
        {0,1,&color_O}, {1,1,&color_O}
}};
static const TetriminoBlocks S_BLOCKS[2] = {
    {{
                        {1,0,&color_S}, {2,0,&color_S},
        {0,1,&color_S}, {1,1,&color_S}
    }},
    {{
        {0,0,&color_S}, 
        {0,1,&color_S}, {1,1,&color_S}, 
                        {1,2,&color_S}
    }}
};
static const TetriminoBlocks T_BLOCKS[4] = {
    {{
        {0,0,&color_T}, {1,0,&color_T}, {2,0,&color_T},
                        {1,1,&color_T}
    }},
    {{
                        {1,0,&color_T}, 
        {0,1,&color_T}, {1,1,&color_T},
                        {1,2,&color_T}
    }},
    {{
                        {1,0,&color_T},
        {0,1,&color_T}, {1,1,&color_T}, {2,1,&color_T},
    }},
    {{
                        {1,0,&color_T}, 
                        {1,1,&color_T}, {2,1,&color_T},
                        {1,2,&color_T}
    }}
};
static const TetriminoBlocks Z_BLOCKS[2] = {
    {{
        {0,0,&color_Z}, {1,0,&color_Z},
                        {1,1,&color_Z}, {2,1,&color_Z}
    }},
    {{
                                        {2,0,&color_Z}, 
                        {1,1,&color_Z}, {2,1,&color_Z}, 
                        {1,2,&color_Z}
    }}
};
