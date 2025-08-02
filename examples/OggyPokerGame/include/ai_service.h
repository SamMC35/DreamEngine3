#ifndef AI_SERVICE_H
#define AI_SERVICE_H

#include <ai_service.h>
#include <map>
#include <variables.h>

Decision decideForPlayer(Hand, std::map<Hand, DecisionFactor> decisionFactorMap);

#endif //AI_SERVICE_H
