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
}Enemy;

typedef struct Bullet{
  Sprite* bSprite;
}Bullet;

vector<Enemy*> enemyList;

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


Font* titleFont = new Font();
Font* scoreFont = new Font();

char* textFont = (char*)"8bit.ttf";

Sprite* cursor;

Color white = {255, 255, 255, 255}; 
Color black = {0, 0, 0, 255};

int menu_index = 0;

bool checkPress = false;

void gameInit(){
  gState = GAME_MENU;
  isPaused = false;

  loadFontFromFile((char*)"8bit.ttf", titleFont, 56);
  loadFontFromFile((char*)"8bit.ttf", scoreFont, 32);

  cursor = new Sprite();
  cursor->color = {255,255,255,200};
}

void gameTitle(){
  
}

void gameMenu(){
  //TODO: write the title screen
  //Title screen

  float fResX = (float)resX;
  float fResY = (float)resY;

  float px = (float)resX/12;
  float py = (float)resY/12;
  
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
        gameLoad();
        break;
      case 1:
        killGame();
        break;
      default:  
        break;
    } 
  }
}

void gameLoad(){
  player = new Player();

  player->pSprite = new Sprite();

  player->pSprite->pos = {300.0f, 448.0f, 64.0f, 32.0f};
  player->pSprite->color = white;
  player->score = 0;

  for(int x = 0; x < 8; x++){
    Enemy* enemy = new Enemy();

    enemy->eSprite = new Sprite();

    enemy->eSprite->pos = {(float)(144 + 64*x), (float)96, (float)48, (float)48};
    enemy->eSprite->color = {255, 0, 0};

    enemyList.push_back(enemy);
  }
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

    bullet->bSprite->pos = {playerPos.x + playerPos.w/2, playerPos.y, 4, 12};
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


void gameplayLogic(){
  //TODO: Player gameplay 
  playerLogic();
  //TODO: Enemy Logic
  //TODO: Bullet Logic
  bulletLogic();
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
  } else{
    writeText((char*)"PAUSED", {0,0,12,12}, white, scoreFont);
  }

  gameplayDraw();

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

