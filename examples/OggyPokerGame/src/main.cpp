#include <iostream>

#include <dream_main.h>


#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480

int main(){
  if(initDreamEngine((char*) "Oggy's Poker Night", SCREEN_WIDTH, SCREEN_HEIGHT, true){
    cout << "Initializing Game" << endl;

    while(!checkQuit()){
      clearScreen();
      //TODO: add game logic
      render();
    }

    quitDreamEngine();
  } else {
    cout << "Failed to initialize dream engine" << endl;
  }
}
