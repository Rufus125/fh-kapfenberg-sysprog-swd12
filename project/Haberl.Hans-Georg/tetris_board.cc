#include "tetris_board.h"
#include "tetris_colors.h"
#include <iostream>

Board::Board(SDL_Surface *window, int offsetX, int offsetY) {
    this->gameOver = false;
    this->points = 0;
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
    this->nextBlock.pos_x = 13;
    this->nextBlock.pos_y = 8;
    this->nextBlock.tetrimino = createRandomTetrimino();
    this->newTetrimino();
    SDL_Flip(this->window);
    for(int x = 0; x < BOARD_BLOCKS_X; x++) {
        for(int y = 0; y < BOARD_BLOCKS_Y; y++) {
            this->oldColors[x][y] = (int*) BOARD_COLOR;
        }
    }
}

bool Board::checkCollide(int dx, int dy) {
    for(int idx = 0; idx < TETRIMINO_BLOCK_NUM; idx++) {
        if(this->getSingleBlockY(idx)+dy >= BOARD_BLOCKS_Y) {
            return true;
        }
        if(this->getSingleBlockX(idx)+dx < 0) {
            return true;
        }
        if(this->getSingleBlockX(idx)+dx >= BOARD_BLOCKS_X) {
            return true;
        }
        if(this->getSingleBlockX(idx)+dx >= 0 && this->getSingleBlockY(idx)+dy >= 0) {
            if(BOARD_COLOR != this->oldColors[this->getSingleBlockX(idx)+dx][this->getSingleBlockY(idx)+dy]) {
                return true;
            }
        }
    }
    return false;
}

void Board::drawBlock(int x, int y, int color) {
    SDL_Rect rect;
    rect.x = this->offsetX + (x*BLOCK_DIMENSIONS);
    rect.y = this->offsetY + (y*BLOCK_DIMENSIONS);
    rect.w = BLOCK_DIMENSIONS;
    rect.h = BLOCK_DIMENSIONS;
    SDL_FillRect(this->window, &rect, color);
}

void Board::drawTetrimino(Block* blocks, int x, int y, int color) {
    for(int blockIdx = 0; blockIdx < TETRIMINO_BLOCK_NUM; blockIdx++) {
        this->drawBlock(blocks[blockIdx].x+x, blocks[blockIdx].y+y, color);
    }

}

void Board::update() {
    SDL_Flip(this->window);
}

void Board::removeTetrimino() {
    this->drawTetrimino(this->currentBlock.tetrimino->getBlocks().blocks,
            this->currentBlock.pos_x,
            this->currentBlock.pos_y,
            *BOARD_COLOR);
}
void Board::addTetrimino() {
    this->drawTetrimino(this->currentBlock.tetrimino->getBlocks().blocks,
            this->currentBlock.pos_x,
            this->currentBlock.pos_y,
            *this->getCurrentBlockColor());
}

void Board::rotateRight() {
    this->currentBlock.tetrimino->right();
    if(this->checkCollide(0, 0)) {
        this->currentBlock.tetrimino->left();
        return;
    }
    this->currentBlock.tetrimino->left();
    this->removeTetrimino();
    this->currentBlock.tetrimino->right();
    this->addTetrimino();
    SDL_Flip(this->window);
}


int Board::getSingleBlockX(int idx) {
    return this->currentBlock.pos_x + this->currentBlock.tetrimino->getBlocks().blocks[idx].x;
}

int Board::getSingleBlockY(int idx) {
    return this->currentBlock.pos_y + this->currentBlock.tetrimino->getBlocks().blocks[idx].y;
}

void Board::newTetrimino() {
    this->drawTetrimino(this->nextBlock.tetrimino->getBlocks().blocks,
            this->nextBlock.pos_x,
            this->nextBlock.pos_y,
            *BOARD_COLOR);
    this->currentBlock.tetrimino = this->nextBlock.tetrimino;
    this->currentBlock.pos_x = 3;
    this->currentBlock.pos_y = -2;
    this->drawTetrimino(this->currentBlock.tetrimino->getBlocks().blocks,
            this->currentBlock.pos_x,
            this->currentBlock.pos_y,
            *this->getCurrentBlockColor());
    this->nextBlock.tetrimino = createRandomTetrimino();
    this->drawTetrimino(this->nextBlock.tetrimino->getBlocks().blocks,
            this->nextBlock.pos_x,
            this->nextBlock.pos_y,
            *this->nextBlock.tetrimino->getBlocks().color);
}

bool Board::checkRow(int row) {
    for(int col=0; col<BOARD_BLOCKS_X; col++) {
        if(BOARD_COLOR == this->oldColors[col][row]) {
            return false;
        }
    }
    return true;
}

void Board::deleteRow(int toDelete) {
    for(int row=toDelete-1; row >= 0; row--) {
        for(int col=0; col<BOARD_BLOCKS_X; col++) {
            oldColors[col][row + 1]=oldColors[col][row];
            this->drawBlock(col, row+1, *oldColors[col][row]);
        }
    }
    for(int col=0; col<BOARD_BLOCKS_X; col++) {
        oldColors[col][0] = (int*) BOARD_COLOR;
        this->drawBlock(col, 0, *BOARD_COLOR);
    }
}

bool Board::down() {
    if(this->checkCollide(0, 1)) {
        for(int idx=0; idx < TETRIMINO_BLOCK_NUM; idx++) {
            if(this->getSingleBlockY(idx) < 0) {
                this->gameOver=true;
            }
        }
        for(int idx=0; idx < TETRIMINO_BLOCK_NUM; idx++) {
           oldColors[this->getSingleBlockX(idx)][this->getSingleBlockY(idx)] = this->getCurrentBlockColor();
        }
        int rows = 0;
        for(int row=BOARD_BLOCKS_Y-1; row >= 0; row--) {
            if(checkRow(row)) {
                deleteRow(row);    
                row++;
            }
        }
        if(rows == 4) {
            this->points+=800;
        } else {
            this->points+=100;
        }
        if(this->points>999999) {
            this->points=999999;
            this->gameOver = true;
        }

        delete(this->currentBlock.tetrimino);
        this->newTetrimino();
        return true;
    }

    this->removeTetrimino();
    this->currentBlock.pos_y++;
    this->addTetrimino();
    SDL_Flip(this->window);
    return false;
}

void Board::drop() {
    while(!this->down());
}

void Board::left() {
    if(this->checkCollide(-1, 0)) {
        return;
    }
    this->removeTetrimino();
    this->currentBlock.pos_x--;
    this->addTetrimino();
    SDL_Flip(this->window);
}

void Board::right() {
    if(this->checkCollide(1, 0)) {
        return;
    }
    this->removeTetrimino();
    this->currentBlock.pos_x++;
    this->addTetrimino();
    SDL_Flip(this->window);
}

int* Board::getCurrentBlockColor() {
    return this->currentBlock.tetrimino->getBlocks().color;
}

Board::~Board() {
    if(this->currentBlock.tetrimino!=NULL) {
        delete(this->currentBlock.tetrimino);
    }
}


