#ifndef MAIN_H
#define MAIN_H

bool initDreamEngine(char*, int, int, bool);             // Initialize Dream Engine
void quitDreamEngine();                                 // Close Dream Engine 
bool checkQuit();                                       // Check if quit is pressed or notn
void render();                                          // Render screen
void clearScreen();                                     // Clears the screen

#endif
