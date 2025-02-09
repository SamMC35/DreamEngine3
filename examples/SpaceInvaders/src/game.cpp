#include <iostream>
#include <dream.h>
#include <vector>

using namespace std;

typedef enum GameState{
  GAME_MENU,
  GAME_PLAYING
}GameState;

typedef struct Player{
  Sprite* pSprite;
  int score;
}Player;

typedef enum MainMenu{
  START_GAME,
  EXIT_GAME
}MainMenu;

typedef enum PauseMenu{
  CONTINUE,
  EXIT
}PauseMenu;

GameState gState;
bool isPaused;

void gameInit(){
  gState = GameState.GAME_MENU;
  isPaused = false;
}

void gameMenu(){
  //TODO: write the title screen
  //TODO: process input
}

void gameplayLogic(){
  //TODO: Player Logic
  
  float moveX =  

  //TODO: Enemy Logic
  //TODO: Bullet Logic
}

void gameplayDraw(){

}

void gamePlay(){
  if(!isPaused){
    gameplayLogic();
  } else{

  }


}

void gameProcess(){
  switch(gState){
    case GAME_MENU:
      gameMenu();
      break;
    
    case GAME_PLAYING:
      gamePlay();
      break;

    default:
      cerr << "Wrong State:" << gState << endl;
  }
}
