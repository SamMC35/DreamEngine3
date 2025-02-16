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
  GAME_PLAYING,
  GAME_TITLE
}GameState;

typedef struct Player{
  Sprite* pSprite;
  int score;
}Player;

Player* player = NULL;

typedef enum MainMenu{
  START_GAME = 0,
  EXIT_GAME = 1
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
Sprite* title;

Color white = {255, 255, 255, 255}; 
Color black = {0, 0, 0, 255};

int menu_index = 0;

bool checkPress = false;

float fResX;
float fResY;

float px;
float py;

void gameInit(){
  gState = GAME_TITLE;
  isPaused = false;

  loadFontFromFile((char*)"8bit.ttf", titleFont, 56);
  loadFontFromFile((char*)"8bit.ttf", scoreFont, 32);

  player = new Player();

  player->pSprite = new Sprite();
  player->pSprite->pos = {840.0f, 720.0f, 120.0f, 40.0f};
  player->pSprite->color = white;

  cursor = new Sprite();
  cursor->color = {255,255,255,200};

  fResX = (float)resX;
  fResY = (float)resY;

  px = fResX/12;
  py = fResY/12;

  title = new Sprite();
  title->pos = {fResX/6 - (px/4), -16, 0, 0};

  cout << "ResX: " << resX << " ResY: " << resY << endl;
  cout << "fResX: " << fResX << " fResY: " << fResY << endl;
}

void gameTitle(){
  title->pos.y += 0.4f;
  writeText((char*)"SPACE INVADERS", {fResX/6 - (px/4), title->pos.y, 0, 0}, white, titleFont);

  if(title->pos.y >= (fResY/8) || checkGamepadPress(0, START)){
    gState = GAME_MENU;
  }

}

void gameMenu(){
  //TODO: write the title screen
  //Title screen
  
  
  
  writeText((char*)"SPACE INVADERS", {fResX/6 - (px/4), fResY/8, 0, 0}, white, titleFont);
  

  //Menu items
  writeText((char*)"PLAY", {fResX/2.4f, fResY/1.5f, 0, 0}, white, scoreFont);
  writeText((char*)"QUIT", {fResX/2.4f, fResY/1.5f + py, 0, 0}, white, scoreFont);



  if(checkGamepadHold(0, DPadUp)){
    menu_index--;
  } else if(checkGamepadHold(0, DPadDown)){
    menu_index++;
  }

  if(menu_index > 1){
    menu_index = 0;
  } else if(menu_index < 0){
    menu_index = 1;
  }

  Vector2 cursorPos;

  switch(menu_index){
    case 0:
      cursorPos = {fResX/2.4f, fResY/1.5f + 6.0f, 88, 36};
      break;
    
    case 1:
      cursorPos = {fResX/2.4f, fResY/1.5f + 6.0f + py, 88, 36};
      break;

    default:
      break;
  }
 

  cursor->pos = cursorPos;

  drawRectangle(cursor);
  
  switch(menu_index){
    case 0:
      writeBlendedText((char*)"PLAY", {fResX/2.4f, fResY/1.5f, 0, 0}, black, scoreFont);
      break;
    
    case 1:
      writeBlendedText((char*)"QUIT", {fResX/2.4f, fResY/1.5f + py, 0, 0}, black, scoreFont);
      break;

    default:
      break;
  }

  
  
  //Logic checkPress

  if(checkGamepadPress(0, A)){
    switch (menu_index) {
      case 0:
        gState = GAME_PLAYING;
        break;
      case 1:
        killGame();
      default:  
        break;
    } 
  }
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
    writeText((char*)"PAUSED", {0,0,12,12}, white, scoreFont);
  }



  if(checkGamepadHold(0, START)){
    isPaused = !isPaused;
  }

}

void gameProcess(){
  switch(gState){
    case GAME_TITLE:
      gameTitle();
      break;

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
