#include <iostream>
#include <dream_main.h>
#include <system.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480

int main(){
  if(initDreamEngine((char*) "Oggy's Poker Night", SCREEN_WIDTH, SCREEN_HEIGHT, true)){
    cout << "Initializing Game" << endl;

    initSystems();

    while(!checkQuit()){
      clearScreen();
      executeSystemLoop();
      render();
    }

    quitDreamEngine();
  } else {
    cout << "Failed to initialize dream engine" << endl;
  }
}
