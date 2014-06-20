#include "tetris.h"
#include "tetris_window.h"
#include "tetris_blocks.h"
#include "tetris_board.h"
#include "tetris_input.h"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <algorithm>
#include "tetris_highscore.h"

using namespace std;

void menu();
int startGame();

int main(int argc, char **argv) {
    //suppress echo
    system("stty -echo");
    //go to RAW mode
    system("stty cbreak");

    menu();

    //enable echo again
    system("stty echo");
    //go to COOKED mode
    system("stty -cbreak");

    return (0);
}

void menu() {
    int option;
    do {
        system("clear");
        cout << "press number:" << endl;
        cout << "1.....new game" << endl;
        cout << "2.....set color style" << endl;
        cout << "3.....show highscore" << endl;
        cout << "4.....show key binding" << endl;
        cout << "ESC...quit" << endl << endl;

        option = getchar();

        int newHighscore = 0;
        int points = 0;
        char buffer[4] = {};
        int gameId = -1;
        switch(option - 48) {
            case 1:
                while(true) {
                    gameId = getNewId();
                    if(gameId <= 0) {
                        cout << "could not get a new game id, which is needed to save the highscore." << endl;
                        cout << "without an id you cannot save your score, do you want to try again (Y/n)?" << endl;
                        if(getchar() != 110) {
                            continue;
                        }
                    }
                    break;
                }
                points = startGame();
                system("clear");
                cout<<"SCORE: " << points << "\n\n";
                if(gameId <= 0) {
                    cout << "press any button to go back to the main menu." << endl;
                    getchar();
                    break;
                }
                cout<<"checking if you have achived a new highscore..." << endl;
                while(1) {
                    newHighscore = checkScore(points);
                    if(newHighscore < 0) {
                        cout << "error retrieving scores!" << endl;
                        cout << "do you want to try again(Y/n)?.";
                        if(getchar() != 110) {
                            continue;
                        }
                    } 
                    break;
                }
                if(newHighscore > 0) {
                    system("clear");
                    cout<<"Congratulations: Your score could be the new number " << newHighscore << "!" << endl;
                    cout<<"Do you want to upload your score? (Y/n)" << endl;
                    if(getchar() != 110) {
                        while(sendScore(gameId, buffer, points) < 0) {
                            cout << "error sending scores!" << endl;
                            cout << "do you want to try again(Y/n)?.";
                            if(getchar() == 110) break;
                        }
                    }
                }
            break;
            case 2:
                system("clear");
                cout << "select color style:" << endl;
                cout << "1...VADIM_GERASIMOV" << endl;
                cout << "2...MICROSOFT" << endl;
                cout << "3...SEGA" << endl;
                cout << "4...THE_NEW_TETRIS" << endl;
                cout << "5...THE_TETRIS_COMPANY" << endl;
                cout << "6...ATARI" << endl;
                cout << "7...TETRIS_THE_SOVIET_MIND_GAME" << endl;
                cout << "8...GAMEBOY_COLOR" << endl;
                do {
                    option = getchar();
                } while (option - 48 < 1 || option - 48 > 8);
                switch(option - 48) {
                    case 1:
                        setColorStyle(VADIM_GERASIMOV);
                        break;
                    case 2:
                        setColorStyle(MICROSOFT);
                        break;
                    case 3:
                        setColorStyle(SEGA);
                        break;
                    case 4:
                        setColorStyle(THE_NEW_TETRIS);
                        break;
                    case 5:
                        setColorStyle(THE_TETRIS_COMPANY);
                        break;
                    case 6:
                        setColorStyle(ATARI);
                        break;
                    case 7:
                        setColorStyle(TETRIS_THE_SOVIET_MIND_GAME);
                        break;
                    case 8:
                        setColorStyle(GAMEBOY_COLOR);
                        break;
                }
            break;
            case 3:
                printScores();
                cout << "Press any button to go back to the main menu..." << endl << endl;
                getchar();
            break;
            case 4:
                system("clear");
                cout << "arrow up......flip right" << endl;
                cout << "arrow left....move left" << endl;
                cout << "arrow right...move right" << endl;
                cout << "arrow down....speed up" << endl;
                cout << "space.........drop" << endl;
                cout << "ESC...........end game" << endl << endl;
                cout << "Press any button to go back to the main menu..." << endl << endl;
                getchar();
                break;
        }
    } while (option != 27);
}

int startGame() {

    Window* window = new Window();
    Input* input = new Input(window->getEvent());
    Board* board = new Board(window->getScreen(), BOARD_OFFSET_X, BOARD_OFFSET_Y); 
    int down = 0;
    BOARD_COLOR = (int *) &BLACK;

    bool running = true;
    int interval = 250;
    int drops = 0;

    do {
        Key key = input->getKey();
        if(key == PAUSE) {
            Key key2;
            do {
                key2 = input->getKey();
                if(key2==ESC) {
                    running = false;
                    break;
                }
            } while(key2 != PAUSE);
        }
        if(key == ESC) running = false;
        if(!running) break;
        if(key == LEFT) {
            board->left();
        }
        if(key == RIGHT) {
            board->right();
        }
        if(key == DOWN) {
            if(board->down()) {
                drops++;
            }
        }
        if(key == UP) {
            board->rotateRight();
        }
        if(key == SPACE) {
            board->drop();
            drops++;
        }

        if(board->gameOver) {
            break;
        }

        board->update();

        usleep(1000);
        if(down++>interval - min((drops / 10), 225)) {
            down = 0;
            if(board->down()) {
                drops++;
            }
            if(board->gameOver) {
                break;
            }
        }
        
    } while (running);

    int points = board->points;
    delete (board);
    delete (input);
    delete (window);
    return points;
}

