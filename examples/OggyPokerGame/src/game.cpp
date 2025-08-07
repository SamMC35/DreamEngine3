#include <game.h>
#include <iostream>

#include <dream_text.h>

GameState gameState;

unordered_map<string, Timer*> timers;

auto menu_text = (char*) "MENU";

Vector2 menu_pos = {240, 40, 32, 32};
constexpr Color white = {255, 255, 255, 255};

Font* font = new Font();

void initGame(){
  //Init states
  gameState = INTRO;

  auto* timer = new Timer();
  timer->max_time = 600;
  timer->current_time = 0;
  timer->active = true;

  timers["intro"] = timer;

  loadFontFromFile((char*)"8bit.ttf", font, 16);
}

void processIntro() {
  writeText(menu_text, menu_pos, white, font);

  menu_pos.x += 0.4f;
  menu_pos.y += 0.4f;

  if (const auto timer = timers["intro"]; timer->current_time > timer->max_time) {
    gameState = MENU;
    timer->active = false;
  }
}

void processTimers() {
  for (const auto& [timer_name, timer] : timers) {
    if (timer->active) {
      timer->current_time++;
    }
  }
}

void processMenu() {

}

void processGame() {

}

void executeGameLoop() {
  processTimers();

  switch(gameState) {
    case INTRO:
      processIntro();
      break;
    case MENU:
      processMenu();
      break;
    case GAME:
      processGame();
    default:
      std::cerr << "Unrecognized game state" << std::endl;
  }
}
