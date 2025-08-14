
#ifndef MENU_SERVICE_H
#define MENU_SERVICE_H
#include <dream_collections.h>
#include <dream_variables.h>
#include <variables.h>

#include "dream_graphics.h"
#include "variables.h"
#include "variables.h"
#include "variables.h"

typedef struct MenuOption {
	char* name;
	Vector2 pos;
}MenuOption;

typedef struct MenuBox {
	Sprite* boxSprite;
	Sprite* borderSprite;

	int borderSize;

	Color selectedColor;
	Color baseColor;
}MenuBox;

class MenuService {
private:
	CircularList<MenuOption*> menuOptions;
	MenuBox* menuBox;

	Font* font;


	std::list<MenuOption*>::iterator currentOption;

public:
	MenuService(CircularList<MenuOption*> &menuOptions, MenuBox* menuBox, Font* font);

	void renderMenu();
	void processInputs();
	void initCurrentOption();
	MenuOption* getCurrentMenuOption() const;

	static bool pollInput();

	~MenuService();
};

#endif //MENU_SERVICE_H
