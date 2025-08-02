#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include "variables.h"

using namespace std;

typedef struct Player {
    char* name;
    int wallet;
    int bet;
    vector<Card*> cards;
    map<Hand, DecisionFactor*> decisionMap;
    Hand hand;
    Decision decision;
}Player;

#endif //PLAYER_H
