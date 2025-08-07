#include <game.h>

#include <dream_graphics.h>
#include <dream_variables.h>
#include <dream_gamepad.h>

#include <iostream>

#include "dream_sound.h"

using namespace std;


constexpr float UNIT =  15.0f;
constexpr Color white = {255, 255, 255};
constexpr Color black = {0, 0, 0};
constexpr Color gray = {154, 181, 181};


Sprite* player;
Sprite* enemy;
Sprite* ball;

Sprite* bg;

int ballMoveX, ballMoveY;

typedef enum GameState {
    NOT_PLAYING,
    PLAYING
}GameState;

GameState state = NOT_PLAYING;

void initGame() {
    player = new Sprite();

    player->pos = {30.0f, 60.0f, UNIT, UNIT*6};
    player->color = black;

    enemy = new Sprite();

    enemy->pos = {675.0f, 300.0f, UNIT, UNIT*6};
    enemy->color = black;

    ball = new Sprite();

    ball->pos = {480.0f-UNIT, 240.0f-UNIT, UNIT, UNIT};
    ball->color = black;

    bg = new Sprite();
    bg->pos = {0, 0, 720, 480};
    bg->color = gray;

    ballMoveX = 1;
    ballMoveY = 1;
}

void drawGame() {
    drawRectangle(bg);

    drawRectangle(player);
    drawRectangle(ball);
    drawRectangle(enemy);
}

void notPlayingBallLogic() {
    ball->pos.x += ballMoveX * 4.0f;
    ball->pos.y += ballMoveY * 4.0f;

    if (ball->pos.x + ball->pos.w > 720 || ball->pos.x < 0) {
        ballMoveX = -ballMoveX;
        playBeep(1, 440, 100);
    }
    if (ball->pos.y + ball->pos.h > 480 || ball->pos.y < 0) {
        ballMoveY = -ballMoveY;
        playBeep(1, 440, 100);
    }
}

void logicGame() {
    int moveY = checkGamepadPress(0, DPadDown) - checkGamepadPress(0, DPadUp);

    if (moveY != 0) {
        player->pos.y += (moveY * 4.0f);
    }
}

void processOneLoop() {
    switch (state) {
        case NOT_PLAYING:
            notPlayingBallLogic();
            break;
        case PLAYING:
            break;
        default:
            cerr << "Invalid state!" << endl;
    }

    logicGame();
    drawGame();
}
