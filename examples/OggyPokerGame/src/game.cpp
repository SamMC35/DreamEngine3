#include <game.h>
#include <iostream>
#include <dream_main.h>

GameState gameState;

void initGame(){
  //Init states
  gameState = INTRO;
}

void processIntro() {

}

void executeGameLoop() {
  switch (gameState) {
    INTRO:
      processIntro();
    default:
      std::cerr << "Unrecognized game state" << std::endl;
  }
}
