#include <menu_service.h>

#include "dream_gamepad.h"
#include "dream_graphics.h"
#include "dream_sound.h"
#include "dream_text.h"

MenuService::MenuService(CircularList<MenuOption *> &menuOptions, MenuBox* menuBox, Font* font) {
	this->menuBox = menuBox;
	this->menuOptions = menuOptions;
	this->currentOption = menuOptions.begin();
	this->font = font;
}

void MenuService::processInputs() {
	if (checkGamepadHold(0,DPadUp)) {
		currentOption = menuOptions.next(currentOption);
		playBeep(0, 440, 100);
	} else if (checkGamepadHold(0,DPadDown)) {
		currentOption = menuOptions.prev(currentOption);
		playBeep(0, 440, 100);
	}
}

void MenuService::initCurrentOption() {
	currentOption = menuOptions.begin();
}

void MenuService::renderMenu() {
	//Render box
	drawOutlinedRectangle(menuBox->boxSprite, 8, {255, 255, 255});

	//Render menu items
	for (auto it = menuOptions.begin(); it != menuOptions.end(); ++it) {
		const MenuOption* menuOption = menuOptions.get(it);

		Color menuColor;

		if (menuOption == menuOptions.get(currentOption)) {
			menuColor = menuBox->selectedColor;
		} else {
			menuColor = menuBox->baseColor;
		}

		writeText(menuOption->name, menuOption->pos, menuColor, font);
	}
}

bool MenuService::pollInput() {
	if (checkGamepadHold(0,A)) {
		return true;
	}

	return false;
}


MenuOption* MenuService::getCurrentMenuOption() const {
	return *currentOption;
}

MenuService::~MenuService() {
	delete menuBox->boxSprite;
	delete menuBox->borderSprite;

	delete menuBox;
	delete font;

	for (const auto option : menuOptions) {
		delete[] option->name;
	}

}

