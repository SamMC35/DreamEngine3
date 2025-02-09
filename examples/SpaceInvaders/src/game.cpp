#include <iostream>
#include <dream_main.h>
#include <vector>
#include <dream_variables.h>
#include <dream_text.h>
#include <dream_gamepad.h>
#include <dream_graphics.h>

#include <game.h>

#define LEFTPLAYERX 240
#define RIGHTPLAYERX 1680

using namespace std;

typedef enum GameState{
  GAME_MENU,
  GAME_PLAYING
}GameState;

typedef struct Player{
  Sprite* pSprite;
  int score;
}Player;

Player* player = NULL;

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

Font* titleFont = new Font();
Font* scoreFont = new Font();

char* textFont = (char*)"8bit.ttf";

Sprite* cursor;

Color white = {255, 255, 255, 255}; 

int menu_index = 0;

bool checkPress = false;

void gameInit(){
  gState = GAME_MENU;
  isPaused = false;

  loadFontFromFile((char*)"8bit.ttf", titleFont, 48);
  loadFontFromFile((char*)"8bit.ttf", scoreFont, 16);

  player = new Player();

  player->pSprite = new Sprite();
  player->pSprite->pos = {840.0f, 720.0f, 120.0f, 40.0f};
  player->pSprite->color = white;

  cursor = new Sprite();
  cursor->color = white;
}

void gameMenu(){
  //TODO: write the title screen
  //Title screen
  
  writeText((char*)"SPACE INVADERS", {320, 240, 0, 0}, white, titleFont);
  

  //Menu items
  writeText((char*)"PLAY", {720, 720, 0, 0}, white, scoreFont);
  writeText((char*)"QUIT", {720, 780, 0, 0}, white, scoreFont);



  if(checkGamepadPress(0, DPadUp) && !checkPress){
    menu_index--;
    checkPress = true;
  } else if(checkGamepadPress(0, DPadDown) && !checkPress){
    menu_index++;
    checkPress = true;
  }

  if(!checkGamepadPress(0, DPadUp) && !checkGamepadPress(0, DPadDown)){
    checkPress = false;
  }

  if(menu_index > 1){
    menu_index = 0;
  } else if(menu_index < 0){
    menu_index = 1;
  }

  Vector2 cursorPos;

  switch(menu_index){
    case 0:
      cursorPos = {680, 720, 16, 16};
      break;
    
    case 1:
      cursorPos = {680, 780, 16, 16};
      break;

    default:
      break;
  }

  cursor->pos = cursorPos;

  drawRectangle(cursor);
}

void gameplayLogic(){
  //TODO: Player Logic
    

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
      cerr << "Wrong State:" << gState << endl;\
      break;
  }
}
