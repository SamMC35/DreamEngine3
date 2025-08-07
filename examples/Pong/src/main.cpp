#include <dream_main.h>
#include <iostream>
#include <game.h>

using namespace std;


int main() {
    if (initDreamEngine((char*) "Pong", 720, 480, true)) {
        initGame();
        while (!checkQuit()) {
            clearScreen();
            processOneLoop();
            render();
        }
    } else {
        cerr << "Failed to initialize Dream engine" << endl;
    }
}