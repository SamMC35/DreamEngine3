#ifndef GAME_H
#define GAME_H

typedef enum GameState {
    INTRO,
    GAME,
    MENU
}GameState;

void initGame();        //Init Game
void executeGameLoop(); //Execute a single loop
void closeGame();       //Close all the pointers


#endif
