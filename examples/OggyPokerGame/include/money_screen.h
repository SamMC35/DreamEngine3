#ifndef MONEY_SCREEN_H
#define MONEY_SCREEN_H

#include "variables.h"

#include <vector>

#include "dream_variables.h"

using namespace std;

class MoneyScreen {

  vector<PlayerData *> playerDataList;
  bool shouldProceed = false;

  Font *textFont;

public:
  void moneyScreenInit(vector<PlayerData *>,
                       Font *textFont); // Init money screen
  void moneyScreenRender();             // Render money screen
  void calculateAnimation();            // Animate table

  bool returnShouldProceed();
};

#endif // !MONEY_SCREEN_H
