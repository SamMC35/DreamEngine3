#include <game.h>

#include <dream_graphics.h>
#include <dream_variables.h>
#include <dream_gamepad.h>
#include <dream_main.h>

#include <iostream>
#include <sstream>
#include <random>

#include <dream_sound.h>
#include <dream_text.h>

using namespace std;


constexpr float UNIT =  15.0f;
constexpr Color white = {255, 255, 255};
constexpr Color black = {0, 0, 0};
constexpr Color gray = {154, 181, 181};


Sprite* player;
Sprite* enemy;
Sprite* ball;

Sprite* bg;

int hits = 0;

int last_hit = 0;           //0 for enemy, 1 for player

float ballMoveX, ballMoveY;

typedef enum GameState {
    NOT_PLAYING,
    PLAYING,
    WAITING
}GameState;

GameState state = NOT_PLAYING;


int gP1Score, gP2Score;

float ballSpeed = 4.0f;
float enemyYVel = 3.2f;

Timer gWaitTimer;
Timer gAiReactTimer;

Font* font = new Font();

Vector2 ballInitPos = {480.0f-UNIT, 240.0f-UNIT, UNIT, UNIT};

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(-3.0f, 3.0f);

void initGame() {
    player = new Sprite();

    player->pos = {30.0f, 60.0f, UNIT, UNIT*6};
    player->color = black;

    enemy = new Sprite();

    enemy->pos = {675.0f, 300.0f, UNIT, UNIT*6};
    enemy->color = black;

    ball = new Sprite();


    ball->pos = ballInitPos;
    ball->color = black;

    bg = new Sprite();
    bg->pos = {0, 0, 720, 480};
    bg->color = gray;

    ballMoveX = 1;
    ballMoveY = 1;

    loadFontFromFile((char*)"8bit.ttf", font, 32);


}

void drawGame() {
    drawRectangle(bg);

    drawRectangle(player);
    drawRectangle(ball);
    drawRectangle(enemy);

    stringstream p1Score;
    p1Score << gP1Score;

    stringstream p2Score;
    p2Score << gP2Score;

    writeText((char*)p1Score.str().c_str(), {120, 15, 0, 0}, white, font);
    writeText((char*)p2Score.str().c_str(), {560, 15, 0, 0}, white, font);

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

    if (checkGamepadPress(0, A)) {
        ball->pos.x = 360.0f-UNIT;
        ball->pos.y = 240.0f-UNIT;

        ballMoveX = -1;
        ballMoveY = -1;

        bg->color = black;

        player->color = white;
        enemy->color = white;
        ball->color = white;

        state = PLAYING;
    }
}

void playerLogic() {
    int moveY = checkGamepadPress(0, DPadDown) - checkGamepadPress(0, DPadUp);

    float yVel = 4.0f;

    if (moveY != 0) {
        float moveYVel = (moveY * yVel);
        float tempPos = player->pos.y + moveYVel;
        if (tempPos + player->pos.h < 480 && tempPos > 0) {
            player->pos.y = tempPos;
        }
    }
}

void ballLogic() {
    ball->pos.x += ballMoveX * ballSpeed;
    ball->pos.y += ballMoveY * ballSpeed;

    if (ball->pos.y + ball->pos.h > 480 || ball->pos.y < 0) {
        ballMoveY = -ballMoveY;
        playBeep(1, 440, 100);
    }
}

float errorFactor = 0.0f;

void enemyLogic() {

    gAiReactTimer.current_time++;

    if (gAiReactTimer.current_time > 10) {
        errorFactor = dist(gen);
        gAiReactTimer.current_time = 0;
    }

    if (enemy->pos.y > (ball->pos.y + errorFactor)) {
        enemy->pos.y -= enemyYVel;
    } else if (enemy->pos.y + enemy->pos.h < (ball->pos.y + errorFactor)) {
        enemy->pos.y += enemyYVel;
    }
}

void calculateBallTrajectory(const Vector2 paddlePos, const Vector2 ballPos) {
    if (collisionCheck(paddlePos, ballPos)) {
        float ballPosYRel = ballPos.y + paddlePos.y;

        if (ballPosYRel > paddlePos.y) {
            ballMoveX = -ballMoveX;
            if (ballPosYRel < (paddlePos.y + UNIT * 1)) {
                ballMoveY = -0.866f;
            }
            if (ballPosYRel < (paddlePos.y + UNIT * 2)) {
                ballMoveY = -0.707f;
            } else if (ballPosYRel < (paddlePos.y + UNIT * 3)) {
                ballMoveY = -0.5f;
            } else if (ballPosYRel < (paddlePos.y + UNIT * 4)) {
                ballMoveY = 0.5f;
            }else if (ballPosYRel < (paddlePos.y + UNIT * 5)) {
                ballMoveY = 0.707f;
            } else if (ballPosYRel < (paddlePos.y + UNIT * 6)) {
                ballMoveY = 0.866f;
            }
        } else {
            ballMoveY = -ballMoveY;
        }
        hits++;

    }
}

void changeToWait() {
    state = WAITING;
    gWaitTimer.current_time = 0;
    gWaitTimer.max_time = 120;
}

void checkCollision() {
    //Player collision
    calculateBallTrajectory(player->pos, ball->pos);
    calculateBallTrajectory(enemy->pos, ball->pos);

    if (ball->pos.x + ball->pos.w < 0 ) {
        changeToWait();
        ballMoveX = -1;
        gP2Score++;
    } else if (ball->pos.x > 720) {
        changeToWait();
        ballMoveX = 1;
        gP1Score++;
    }
}

void resetBall() {
    ball->pos = ballInitPos;
    ballSpeed = 4.0f;
    enemyYVel = 3.2f;
    hits = 0;
}

void processTimers() {
    if (gWaitTimer.current_time > gWaitTimer.max_time) {
        state = PLAYING;
        resetBall();
    }
    gWaitTimer.current_time++;
}

void checkResults() {
    if (gP1Score > 10 || gP2Score > 10) {
        state = NOT_PLAYING;
        gP2Score = 0;
        gP1Score = 0;
        resetBall();
        bg->color = gray;
        player->color = black;
        enemy->color = black;
        ball->color = black;
    }
};

void processOneLoop() {
    switch (state) {
        case NOT_PLAYING:
            notPlayingBallLogic();
            break;
        case PLAYING:
            ballLogic();
            enemyLogic();
            checkCollision();
            checkResults();
            break;
        case WAITING:
            processTimers();
            break;
        default:
            cerr << "Invalid state!" << endl;
    }

    playerLogic();
    drawGame();
}
