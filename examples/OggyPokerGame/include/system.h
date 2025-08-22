#ifndef GAME_H
#define GAME_H

// typedef enum GameState { INTRO, GAME, MENU, MONEY_SELECT } GameState;

void initSystems();       // Init Game
void executeSystemLoop(); // Execute a single loop
void closeSystem();       // Close all the pointers
void switchState();

#endif
