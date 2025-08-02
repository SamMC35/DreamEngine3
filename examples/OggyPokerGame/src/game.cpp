#include <game.h>
#include <iostream>

GameState gameState;


void initGame(){
  //Init states
  gameState = INTRO;
}

void executeGameLoop() {
  switch (gameState) {

    default:
      std::cerr << "Unrecognized game state" << std::endl;
  }
}
