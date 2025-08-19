#include <system.h>
#include <iostream>

#include <dream_text.h>

#include "dream_gamepad.h"
#include "dream_main.h"
#include "menu_service.h"
#include "number_selector.h"

GameState gameState;

unordered_map<string, Timer*> timers;

auto menu_text = (char*) "OGGY Poker Game PH";

Vector2 menu_pos = {240, 40, 32, 32};
constexpr Color white = {255, 255, 255, 255};

Font* font = new Font();

MenuService* menuService;
NumberSelector* numberSelector;

void createMainMenuItems() {
  CircularList<MenuOption*> menuOptions;

  MenuOption* play = new MenuOption();
  play->name = (char*)"Play";
  play->pos = {128,116,16, 16};

  MenuOption* quit = new MenuOption();
  quit->name = (char*)"Quit";
  quit->pos = {128,160,16, 16};

  menuOptions.add(play);
  menuOptions.add(quit);

  MenuBox* menuBox = new MenuBox();

  Sprite* boxSprite = new Sprite();
  boxSprite->pos = {120, 120, 96, 96};
  boxSprite->color = {219,31, 134};

  menuBox->boxSprite = boxSprite;

  Sprite* borderSprite = new Sprite();
  borderSprite->pos = {96, 96, 144, 144};
  borderSprite->color = {219,123, 134};

  menuBox->borderSprite = borderSprite;

  menuBox->selectedColor = white;
  menuBox->baseColor = {0,0,0};

  menuService = new MenuService(menuOptions, menuBox, font);
  menuService->initCurrentOption();

  vector<int> numbers;

  numbers.push_back(2);
  numbers.push_back(3);
  numbers.push_back(4);

  numberSelector = new NumberSelector(numbers, {12, 34, 56, 67}, white, font);
}

void initSystems(){
  //Init states
  gameState = INTRO;

  auto* timer = new Timer();
  timer->max_time = 600;
  timer->current_time = 0;
  timer->active = true;

  timers["intro"] = timer;

  loadFontFromFile((char*)"8bit.ttf", font, 32);

  createMainMenuItems();
}

void processIntro() {
  writeText(menu_text, menu_pos, white, font);

  menu_pos.x += 0.4f;
  menu_pos.y += 0.4f;

  if (checkGamepadHold(0,A)) {
    gameState = MENU;
  }

  numberSelector->renderNumber();
  numberSelector->processInput();

}

void processTimers() {
  for (const auto& [timer_name, timer] : timers) {
    if (timer->active) {
      timer->current_time++;
    }
  }
}

void processMenu(){
  menuService->processInputs();

  if (MenuService::pollInput()) {
    MenuOption* menuOption = menuService->getCurrentMenuOption();

    cout << "Menu Option Selected: " << menuOption->name << endl;

    std::string menuOptionName = menuOption->name;

    if (menuOptionName == "Quit") {
      killGame();
    } else if (menuOptionName == "Play") {
      gameState = GAME;
    } else {
      std::cout << "Invalid menu option: " << menuOptionName << std::endl;
    }

  }

  //Render OGGYPokerGame title card
  

  menuService->renderMenu();
}

void processGame() {

}

void executeSystemLoop() {
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
      break;
    default:
      std::cerr << "Unrecognized game state" << std::endl;
      killGame();
      break;
  }
}
