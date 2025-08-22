#include "variables.h"
#include <money_screen.h>

#include <vector>

#include "dream_graphics.h"
#include "dream_variables.h"
using namespace std;

int max_time;
int current_time;

int currentIndex;

Sprite *boxSprite;
/*Sprite *alphaSprite;*/

void MoneyScreen::moneyScreenInit(vector<PlayerData *> playerDataList) {
  max_time = 30;
  current_time = 0;

  currentIndex = -1;

  boxSprite = new Sprite();

  boxSprite->pos = {96, 48, 528, 384};
  boxSprite->color = {0, 0, 0, 128};
}

void MoneyScreen::calculateAnimation() {
  if (current_time > max_time) {
    currentIndex++;
    if (currentIndex > playerDataList.max_size()) {
      shouldProceed = true;
    }
    current_time = 0;
  }

  current_time++;
}

void MoneyScreen::moneyScreenRender() {
  // Draw border

  Color white = {255, 255, 255};
  drawOutlinedRectangle(boxSprite, 8, white);
}

bool MoneyScreen::returnShouldProceed() { return shouldProceed; }
