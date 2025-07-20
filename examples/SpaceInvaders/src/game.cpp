#include <iostream>
#include <dream_main.h>
#include <vector>
#include <dream_variables.h>
#include <dream_text.h>
#include <dream_gamepad.h>
#include <dream_graphics.h>

#include <dream_sound.h>

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

float leftX = 96.0f, rightX = 624.0f;

float eVelX = 4.0f;

int eMoveDir = -1;

Timer* invaderTimer;


vector<int> speedChangeNums = {2, 5, 10, 20, 30};

int lastThreshold = -1;
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
      play_beep(0, 440, 50);
      menu_index--;
    } else if(checkGamepadHold(0, DPadDown)){
      play_beep(0, 440, 50);
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
  
  loadTexture(player->pSprite, (char*) "examples/SpaceInvaders/resources/spaceShip.png");

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

  invaderTimer = new Timer();

  invaderTimer->max_time = 90;
}

void playerLogic(){
  //Movement

  float velX = 0;

  if(checkGamepadPress(0, DPadLeft)){
    velX = -4; 
  } else if(checkGamepadPress(0, DPadRight)){
    velX = 4;
  }

  if(player->pSprite->pos.x + velX < leftX || player->pSprite->pos.x+player->pSprite->pos.w + velX > rightX){
    velX = 0;
  }
  player->pSprite->pos.x += velX;
}

void bulletLogic(){
  if(bullet == NULL && checkGamepadPress(0, A)){
    bullet = new Bullet();
    bullet->bSprite = new Sprite();
    Vector2 playerPos = player->pSprite->pos;

    bullet->bSprite->pos = {playerPos.x + (playerPos.w/2 - 2.0f), playerPos.y, 2, 16};
    bullet->bSprite->color = white;

    play_beep(0, 750, 75);
  }

  if(bullet != NULL){
    float velY = -8.0f;

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
        play_beep(1, 100, 150);
        break;  
    }
  }
}

void enemyLogic(){
  bool moveDown = false;
  

  //Check if invaders need to move down

  for(Enemy* e : enemyList){
    if((((e->eSprite->pos.x - eVelX) < leftX ) && eMoveDir < 0) || ((e->eSprite->pos.x + e->eSprite->pos.w + eVelX) > rightX) && eMoveDir > 0)
    {
      moveDown = true;
      eMoveDir = -(eMoveDir);
      break;
    }
  }

  for(Enemy* e : enemyList){
    if(moveDown){
      e->eSprite->pos.y += 8.0f;
    } else {
      e->eSprite->pos.x += eVelX * eMoveDir;
    }
  }
}

void checkEnemyNumbers(){
  int index = -1;

  for (size_t i = 0; i < speedChangeNums.size(); i++) {
            if (enemyList.size() < speedChangeNums[i]) {
                index = i;
                break;
            }
        }

  if(index != lastThreshold && index != -1){
    lastThreshold = index;
    setMaxTimer(invaderTimer, invaderTimer->max_time/2);

    eVelX *= 1.4f;

    cout << "Changed timer: " << invaderTimer->max_time << endl;
    cout << "Invader speed: " << eVelX << endl;
    cout << "Invader Size: " << enemyList.size() << endl;
  }
}


void gameplayLogic(){
  if(!isAnyButtonPressed()){
    canUseButtons = true;
  }
  if(canUseButtons){
    playerLogic();
    bulletLogic();
    if(invaderTimer->current_time >= invaderTimer->max_time){
      enemyLogic();
      
      resetTimer(invaderTimer);
    }
  }
  if(bullet != NULL){
    checkBulletCollision();
  }
  
  checkEnemyNumbers();
  
  incrementTimer(invaderTimer);
}

void gameplayDraw(){
  renderTexture(player->pSprite);

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

