#include <iostream>
#include <dream_main.h>
#include <game.h>


int main(){
  //Initialize the game
  //
  
  if(initDreamEngine((char*) "Space Invaders", 720, 480, false)){
    
    gameInit();

    while(!checkQuit()){
      clearScreen();
      gameProcess();
      render();
    }

    quitDreamEngine();
  }
  
}
