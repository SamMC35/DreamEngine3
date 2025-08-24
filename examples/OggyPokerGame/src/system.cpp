#include <iostream>
#include <system.h>

#include <dream_text.h>
#include <vector>

#include "dream_gamepad.h"
#include "dream_main.h"
#include "menu_service.h"
#include "money_screen.h"
#include "number_selector.h"
#include "variables.h"

GameState gameState;

unordered_map<string, Timer *> timers;

auto menu_text = (char *)"OGGY Poker Game PH";

Vector2 menu_pos = {240, 40, 32, 32};
constexpr Color white = {255, 255, 255, 255};

Font *titleFont = new Font();
Font *textFont = new Font();

MenuService *menuService;
NumberSelector *numberSelector;

NumberSelector *moneyNumberSelector;

MoneyScreen *moneyScreen;

void createMainMenuItems() {
  CircularList<MenuOption *> menuOptions;

  MenuOption *play = new MenuOption();
  play->name = (char *)"Play";
  play->pos = {128, 116, 16, 16};

  MenuOption *quit = new MenuOption();
  quit->name = (char *)"Quit";
  quit->pos = {128, 160, 16, 16};

  menuOptions.add(play);
  menuOptions.add(quit);

  MenuBox *menuBox = new MenuBox();

  Sprite *boxSprite = new Sprite();
  boxSprite->pos = {120, 120, 96, 96};
  boxSprite->color = {219, 31, 134, 255};

  menuBox->boxSprite = boxSprite;

  Sprite *borderSprite = new Sprite();
  borderSprite->pos = {96, 96, 144, 144};
  borderSprite->color = {219, 123, 134, 255};

  menuBox->borderSprite = borderSprite;

  menuBox->selectedColor = white;
  menuBox->baseColor = {0, 0, 0, 255};

  menuService = new MenuService(menuOptions, menuBox, titleFont);
  menuService->initCurrentOption();

  vector<int> numbers;

  numbers.push_back(2);
  numbers.push_back(3);
  numbers.push_back(4);

  numberSelector =
      new NumberSelector(numbers, {12, 34, 56, 67}, white, titleFont);
}

void initSystems() {
  // Init states
  gameState = INTRO;

  auto *timer = new Timer();
  timer->max_time = 600;
  timer->current_time = 0;
  timer->active = true;

  timers["intro"] = timer;

  loadFontFromFile((char *)"8bit.ttf", titleFont, 32);
  loadFontFromFile((char *)"8bit.ttf", textFont, 16);

  createMainMenuItems();
}

void processIntro() {
  writeText(menu_text, menu_pos, white, titleFont);

  menu_pos.x += 0.4f;
  menu_pos.y += 0.4f;

  if (checkGamepadHold(0, A)) {
    gameState = MENU;
  }

  // numberSelector->renderNumber();
  // numberSelector->processInput();
  //
  moneyScreen = new MoneyScreen();
}

void processTimers() {
  for (const auto &[timer_name, timer] : timers) {
    if (timer->active) {
      timer->current_time++;
    }
  }
}

void processMenu() {
  menuService->processInputs();

  if (MenuService::pollInput()) {
    MenuOption *menuOption = menuService->getCurrentMenuOption();

    cout << "Menu Option Selected: " << menuOption->name << endl;

    std::string menuOptionName = menuOption->name;

    if (menuOptionName == "Quit") {
      killGame();
    } else if (menuOptionName == "Play") {
      gameState = MONEY_SELECT;
      switchState();
    } else {
      std::cout << "Invalid menu option: " << menuOptionName << std::endl;
    }
  }

  // TODO:  Render OGGYPokerGame title card

  menuService->renderMenu();
}

vector<int> moneyNumbers;

void switchState() {
  switch (gameState) {
  case MONEY_SELECT:

    moneyNumbers.push_back(0);
    moneyNumbers.push_back(1);
    moneyNumbers.push_back(0);
    moneyNumbers.push_back(0);

    moneyNumberSelector =
        new NumberSelector(moneyNumbers, {96 + 36, 96 + 36}, white, textFont);

    break;
  default:
    break;
  }
}

void processGame() {}

void processMoneySelect() {
  // Render border
  Sprite *blankSprite = new Sprite();
  blankSprite->pos = {96, 96, 360, 96};
  blankSprite->color = {0, 0, 0, 255};

  drawOutlinedRectangle(blankSprite, 4, {255, 255, 255, 255});

  writeText((char *)"Money Select",
            {blankSprite->pos.x + 12, blankSprite->pos.y + 12}, white,
            textFont);

  moneyNumberSelector->processInput();
  moneyNumberSelector->renderNumber();

  if (checkGamepadHold(0, A)) {
    int moneyInit = moneyNumberSelector->getNumber();
    gameState = MONEY_TABLE;

    vector<PlayerData *> playerDataList;

    vector<char *> names = {"Oggy", "Jack", "Dee Dee", "Marky", "Joey"};

    for (char *name : names) {
      PlayerData *playerData = new PlayerData();
      playerData->name = name;
      playerData->moneyHave = moneyInit;
      playerDataList.push_back(playerData);
    }

    moneyScreen->moneyScreenInit(playerDataList, textFont);
  }
}

void processTable() {
  moneyScreen->moneyScreenRender();
  moneyScreen->calculateAnimation();
}

void executeSystemLoop() {
  processTimers();

  switch (gameState) {
  case INTRO:
    processIntro();
    break;
  case MENU:
    processMenu();
    break;
  case MONEY_SELECT:
    processMoneySelect();
    break;
  case GAME:
    processGame();
    break;
  case MONEY_TABLE:
    processTable();
    break;
  default:
    std::cerr << "Unrecognized game state" << std::endl;
    killGame();
    break;
  }
}
