#ifndef VARIABLES_H
#define VARIABLES_H

#include <dream_variables.h>

typedef enum Suit {
    CLUBS,
    HEARTS,
    DIAMONDS,
    SPADES
}Suit;

typedef enum Rank {
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
}Rank;

typedef struct Card{
    Suit suit;
    Rank rank;
}Card;

typedef enum Hand {
    NONE = 0,
    HIGH_CARD = 1,
    ONE_PAIR = 2,
    TWO_PAIR = 3,
    THREE_OF_A_KIND = 4,
    STRAIGHT = 5,
    FLUSH = 6,
    FULL_HOUSE = 7,
    FOUR_OF_A_KIND = 8,
    STRAIGHT_FLUSH = 9,
    ROYAL_FLUSH = 10
}Hand;

typedef struct DecisionFactor {
    int call;
    int fold;
    int raise;
}DecisionFactor;

typedef enum Decision {
    PLAYING,
    CALLED,
    RAISED,
    FOLDED
}Decision;

typedef enum GameState {
    INTRO,
    MAIN_MENU,
    OPTIONS,
    MONEY_SELECT,
    GAME,
    PAUSED,
    GAME_OVER
}GameState;

typedef struct PlayerData{
  char* name;
  Hand hand;
  int moneyWon;
  int moneyHave;
}

typedef enum PlayState {
    SHUFFLING,
    FIRST_ROUND,
    SECOND_ROUND,
    RESULTS
}PlayState;

#endif
