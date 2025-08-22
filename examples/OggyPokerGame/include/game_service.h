
#ifndef GAME_SERVICE_H
#define GAME_SERVICE_H
#include <list>
#include <map>
#include <string>
#include <variables.h>

typedef struct Player {
  std::string name;
  int money;
  std::list<Card *> cards;
  Hand hand;
  PlayState playState;
  std::map<Hand, DecisionFactor> decisionFactorMap;
} Player;

typedef enum TableState { MONEY, PLAYING_TABLE } TableState;
void initGame();       // Init the game loop
void executeOneLoop(); // One cycle

#endif // GAME_SERVICE_H
