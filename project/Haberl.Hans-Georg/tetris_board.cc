#include "tetris_board.h"
#include "tetris_colors.h"

Board::Board(SDL_Surface *window, int offsetX, int offsetY) {
    this->window = window;
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    SDL_Rect left = {
            offsetX-BLOCK_DIMENSIONS, 
            offsetY, 
            BLOCK_DIMENSIONS, 
            BLOCK_DIMENSIONS*BOARD_BLOCKS_Y};
    SDL_Rect right = {
            offsetX + BLOCK_DIMENSIONS*BOARD_BLOCKS_X, 
            offsetY, 
            BLOCK_DIMENSIONS, 
            BLOCK_DIMENSIONS*BOARD_BLOCKS_Y};
    SDL_Rect bottom = {
            offsetX-BLOCK_DIMENSIONS,
            offsetY+BLOCK_DIMENSIONS*BOARD_BLOCKS_Y,
            BLOCK_DIMENSIONS*(BOARD_BLOCKS_X+2),
            BLOCK_DIMENSIONS};
    SDL_FillRect(this->window, &left, WHITE);
    SDL_FillRect(this->window, &right, WHITE);
    SDL_FillRect(this->window, &bottom, WHITE);
    this->currentBlock.tetrimino = createRandomTetrimino();
    this->currentBlock.pos_x = 3;
    this->currentBlock.pos_y = -TETRIMINO_BLOCK_NUM;
}

void Board::drawTetrimino(Block* blocks, int x, int y, int color) {
    for(int blockIdx = 0; blockIdx < TETRIMINO_BLOCK_NUM; blockIdx++) {
        SDL_Rect rect;
        rect.x = this->offsetX + ((blocks[blockIdx].x+x)*BLOCK_DIMENSIONS);
        rect.y = this->offsetY + ((blocks[blockIdx].y+y)*BLOCK_DIMENSIONS);
        rect.w = BLOCK_DIMENSIONS;
        rect.h = BLOCK_DIMENSIONS;
        SDL_FillRect(this->window, &rect, color);
    }

}

void Board::update() {
    this->drawTetrimino(this->getCurrentBlocks(),
            this->currentBlock.pos_x,
            this->currentBlock.pos_y,
            this->getCurrentBlockColor());
    SDL_Flip(this->window);
}

void Board::left() {
    if(this->currentBlock.pos_x <= 0) {
        return;
    }
    for(int idx = 0; idx < TETRIMINO_BLOCK_NUM; idx++) {
        if(BOARD_COLOR == oldColors
                [(this->currentBlock.pos_x-1) + this->currentBlock.tetrimino->getBlocks().blocks[idx].x]
                [ this->currentBlock.pos_y    + this->currentBlock.tetrimino->getBlocks().blocks[idx].y]) {
            return;
        }
    }
    this->drawTetrimino(this->getCurrentBlocks(),
            this->currentBlock.pos_x,
            this->currentBlock.pos_y,
            *BOARD_COLOR);
    this->currentBlock.pos_x--;
}

void Board::right() {
    if(this->currentBlock.pos_x >= BOARD_BLOCKS_X - 1) {
        return;
    }
    for(int idx = 0; idx < TETRIMINO_BLOCK_NUM; idx++) {
        if(BOARD_COLOR == oldColors
                [(this->currentBlock.pos_x+1) + this->currentBlock.tetrimino->getBlocks().blocks[idx].x]
                [ this->currentBlock.pos_y    + this->currentBlock.tetrimino->getBlocks().blocks[idx].y]) {
            return;
        }
    }
    this->drawTetrimino(this->currentBlock.tetrimino->getBlocks().blocks,
            this->currentBlock.pos_x,
            this->currentBlock.pos_y,
            *BOARD_COLOR);
    this->currentBlock.pos_x++;
}

Block* Board::getCurrentBlocks() {
    return this->currentBlock.tetrimino->getBlocks().blocks;
}

int Board::getCurrentBlockColor() {
    return *this->currentBlock.tetrimino->getBlocks().color;
}

Board::~Board() {
}


