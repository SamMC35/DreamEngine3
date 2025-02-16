#ifndef MAIN_H
#define MAIN_H

#include "dream_variables.h"

bool initDreamEngine(char*, int, int, bool);             // Initialize Dream Engine
void quitDreamEngine();                                 // Close Dream Engine 
bool checkQuit();                                       // Check if quit is pressed or notn
void render();                                          // Render screen
void clearScreen();                                     // Clears the screen

bool collisionCheck(Vector2 a, Vector2 b);              //Checks collision 
void killGame();                                        //Kill game


#endif
