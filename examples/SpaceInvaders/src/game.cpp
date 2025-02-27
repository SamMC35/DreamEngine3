#include <iostream>
#include <dream_main.h>
#include <vector>
#include <dream_variables.h>
#include <dream_text.h>
#include <dream_gamepad.h>
#include <dream_graphics.h>

#include <game.h>

#define LEFTPLAYERX 96
#define RIGHTPLAYERX 624

using namespace std;

void gameLoad();

typedef enum GameState{
  GAME_MENU,
  GAME_PLAYING,
  GAME_TITLE
}GameState;

typedef struct Player{
  Sprite* pSprite;
  int score;
}Player;

typedef struct Enemy{
  Sprite* eSprite;
  int id;
  bool anim;
  bool isDying;
  int row;
  int column;
}Enemy;

typedef struct Bullet{
  Sprite* bSprite;
}Bullet;

vector<Enemy*> enemyList;
vector<Enemy*> killList;


Player* player = NULL;
Bullet* bullet = NULL;

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
bool canUseButtons;


Font* titleFont = new Font();
Font* scoreFont = new Font();

char* textFont = (char*)"8bit.ttf";

Sprite* cursor;
Sprite* pauseBox;

Color white = {255, 255, 255, 255}; 
Color black = {0, 0, 0, 255};

int menu_index = 0;

bool checkPress = false;

float fResX, fResY, px, py;

float titlePosY;

void gameInit(){
  gState = GAME_TITLE;
  isPaused = false;

  loadFontFromFile((char*)"8bit.ttf", titleFont, 56);
  loadFontFromFile((char*)"8bit.ttf", scoreFont, 32);

  fResX = (float)resX;
  fResY = (float)resY;

  px = (float)resX/12;
  py = (float)resY/12;

  cursor = new Sprite();
  cursor->color = {255,255,255,200};

  titlePosY = -12.0f;

  pauseBox = new Sprite();

  pauseBox->pos = {fResX/2.4f,fResY/2.4f,128,48};
  pauseBox->color = black;
}

void gameTitle(){
  writeText((char*)"SPACE INVADERS", {fResX/6 - (px/4), titlePosY, 0, 0}, white, titleFont);

  if(titlePosY < fResY/6){
    titlePosY += 0.5f;
  } else {
    gState = GAME_MENU;
  }

  if(checkAnyGamepadPress()){
    gState = GAME_MENU;
    canUseButtons = false;
  }
}

void gameMenu(){
 

  if(!isAnyButtonPressed()){
    canUseButtons = true;
  }

  writeText((char*)"SPACE INVADERS", {fResX/6 - (px/4), fResY/6, 0, 0}, white, titleFont);
  
  //Menu items
  writeText((char*)"PLAY", {fResX/2.4f, fResY/1.5f, 0, 0}, white, scoreFont);
  writeText((char*)"QUIT", {fResX/2.4f, fResY/1.5f + py, 0, 0}, white, scoreFont);

  

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
      writeText((char*)"PLAY", {fResX/2.4f, fResY/1.5f, 0, 0}, black, scoreFont);
      break;
    
    case 1:
      writeText((char*)"QUIT", {fResX/2.4f, fResY/1.5f + py, 0, 0}, black, scoreFont);
      break;

    default:
      break;
  }

  
  
  //Logic checkPress

  if(canUseButtons){
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
    if(checkGamepadPress(0, A)){
      switch (menu_index) {
        case 0:
          gameLoad();
          gState = GAME_PLAYING;
          break;
        case 1:
          killGame();
          break;
        default:  
          break;
      } 
    }
  }
}

void gameLoad(){
  player = new Player();

  player->pSprite = new Sprite();

  player->pSprite->pos = {300.0f, 448.0f, 48.0f, 24.0f};
  player->pSprite->color = white;
  player->score = 0;

  for(int y = 0; y < 4; y++){
    for(int x = 0; x < 10; x++){
      Enemy* enemy = new Enemy();

      enemy->eSprite = new Sprite();

      enemy->eSprite->pos = {(float)(128 + 48*x), (float)(96 + 48*y), (float)32, (float)32};
      enemy->eSprite->color = {255, 0, 0};

      enemy->column = y+1;
      enemy->row = x+1;

      enemyList.push_back(enemy);
    }
  }
  canUseButtons = false;
}

void playerLogic(){
  //Movement

  float velX = 0;

  if(checkGamepadPress(0, DPadLeft)){
    velX = -4; 
  } else if(checkGamepadPress(0, DPadRight)){
    velX = 4;
  }

  if(player->pSprite->pos.x + velX < LEFTPLAYERX || player->pSprite->pos.x+player->pSprite->pos.w + velX > RIGHTPLAYERX){
    velX = 0;
  }
  player->pSprite->pos.x += velX;
}

void bulletLogic(){
  if(bullet == NULL && checkGamepadPress(0, A)){
    bullet = new Bullet();
    bullet->bSprite = new Sprite();
    Vector2 playerPos = player->pSprite->pos;

    bullet->bSprite->pos = {playerPos.x + playerPos.w/2, playerPos.y, 4, 16};
    bullet->bSprite->color = white;
  }

  if(bullet != NULL){
    float velY = -4;

    bullet->bSprite->pos.y += velY;

    if(bullet->bSprite->pos.y < 0){
      delete bullet;
      bullet = NULL;
    }
  }
}

void checkBulletCollision(){
  killList.clear();

  bool done = false;

  for (auto it = enemyList.begin(); it != enemyList.end(); ++it) {
    if (collisionCheck((*it)->eSprite->pos, bullet->bSprite->pos)) {  
        delete *it;  
        enemyList.erase(it);  
        delete bullet;
        bullet = NULL;
        break;  
    }
  }
}


void gameplayLogic(){
  if(!isAnyButtonPressed()){
    canUseButtons = true;
  }
  if(canUseButtons){
    playerLogic();
    bulletLogic();
  }
  if(bullet != NULL){
    checkBulletCollision();
  }
}

void gameplayDraw(){
  drawRectangle(player->pSprite);

  for(Enemy* e : enemyList){
    drawRectangle(e->eSprite);
  }

  if(bullet != NULL){
    drawRectangle(bullet->bSprite);
  }
}

void gamePlay(){
  if(!isPaused){
    gameplayLogic();
  } 

  gameplayDraw();

  if(isPaused){
    drawRectangle(pauseBox);
    writeText((char*)"PAUSED", {fResX/2.4f,fResY/2.4f,12,12}, white, scoreFont);
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
      cerr << "Wrong State:" << gState << endl;
      break;
  }
}

void freeGame(){
  delete player;

  for(Enemy* enemy : enemyList){
    delete enemy;
  }

  enemyList.clear();

  delete scoreFont;
  delete titleFont;

  delete cursor;
}

