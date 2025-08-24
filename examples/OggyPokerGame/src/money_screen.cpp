#include "dream_sound.h"
#include "dream_text.h"
#include "variables.h"
#include <money_screen.h>

#include <sstream>
#include <vector>

#include "dream_graphics.h"
#include "dream_variables.h"
using namespace std;

int max_time;
int current_time;

int currentIndex;

Sprite *boxSprite;
Sprite *bg;

vector<char *> headers;

vector<Sprite *> lines;
Color white = {255, 255, 255, 255};
void MoneyScreen::moneyScreenInit(vector<PlayerData *> playerDataList,
                                  Font *textFont) {
  max_time = 30;
  current_time = 0;

  currentIndex = 0;

  boxSprite = new Sprite();

  boxSprite->pos = {96, 48, 528, 288};
  boxSprite->color = {45, 105, 35, 255};

  bg = new Sprite();
  bg->pos = {0, 0, 720, 480};
  bg->color = {255, 0, 255, 255};

  this->textFont = textFont;

  for (int i = 2; i <= 7; i++) {
    Sprite *sprite = new Sprite();
    sprite->pos = {96, (float)(48 * i), 624, (float)(48 * i)};
    sprite->color = white;
    lines.push_back(sprite);
  }

  this->playerDataList = playerDataList;

  for (PlayerData *playerData : playerDataList) {
    cout << playerData->name << endl;
    cout << playerData->moneyHave << endl;
  }
}

void MoneyScreen::calculateAnimation() {
  if (current_time > max_time) {
    if (currentIndex >= playerDataList.size() - 1) {
      shouldProceed = true;
      currentIndex = playerDataList.size() - 1;
    } else {
      currentIndex++;
      playBeep(0, 440, 100);
    }
    current_time = 0;
    return;
  }

  // cout << "Current Time: " << current_time << endl;
  current_time++;
}

void MoneyScreen::moneyScreenRender() {
  // Draw border
  drawRectangle(bg);

  drawOutlinedRectangle(boxSprite, 8, white);

  for (Sprite *s : lines) {
    drawLine(s);
  }

  writeText((char *)"Name", {108, 54}, white, textFont);
  writeText((char *)"Hand", {240, 54}, white, textFont);
  writeText((char *)"Money Won", {384, 54}, white, textFont);
  writeText((char *)"Wallet", {528, 54}, white, textFont);

  // Write players

  for (int i = 0; i <= currentIndex; i++) {
    // cout << "Player Data:" << playerData->name << endl;
    //  Name

    PlayerData *playerData = playerDataList.at(i);

    cout << currentIndex << endl;
    writeText((char *)playerData->name, {108, (float)(108 + (48 * i))}, white,
              textFont);
    stringstream moneyHave;
    moneyHave << playerData->moneyHave;
    writeText((char *)moneyHave.str().c_str(), {540, (float)(108 + (48 * i))},
              white, textFont);
  }
}

bool MoneyScreen::returnShouldProceed() { return shouldProceed; }
