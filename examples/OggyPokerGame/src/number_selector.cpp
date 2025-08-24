#include <number_selector.h>
#include <sstream>

#include <dream_text.h>

#include "dream_gamepad.h"
#include "dream_graphics.h"

NumberSelector::NumberSelector(vector<int> integerArray, Vector2 pos,
                               Color color, Font *font) {
  this->integerArray = integerArray;
  this->pos = pos;
  this->color = color;
  this->font = font;
  this->currentPosition = integerArray.size() - 1;

  this->lineSprite = new Sprite();

  this->lineSprite->pos = {pos.x + 2, pos.y + font->textSize.h,
                           font->textSize.w - 2, (float)font->textSize.h / 6};

  cout << "X:" << lineSprite->pos.x << endl;
  cout << "Y:" << lineSprite->pos.y << endl;
  this->lineSprite->color = {255, 255, 255, 255};
}

void NumberSelector::renderNumber() {
  stringstream numString;
  for (int i : integerArray) {
    numString << i;
  }

  writeText((char *)numString.str().c_str(), pos, color, font);
  this->lineSprite->pos.x =
      (pos.x + 2) + ((font->textSize.w) * currentPosition);

  // cout << currentPosition << endl;
  drawRectangle(lineSprite);
}

int NumberSelector::getNumber() {
  stringstream numString;
  for (int i : integerArray) {
    numString << i;
  }
  int number;
  numString >> number;

  return number;
}

void NumberSelector::processInput() {
  if (checkGamepadHold(0, DPadLeft)) {
    if (currentPosition < 1) {
      currentPosition = integerArray.size() - 1;
    } else {
      currentPosition--;
    }
  } else if (checkGamepadHold(0, DPadRight)) {
    if (currentPosition > (integerArray.size() - 2)) {
      currentPosition = 0;
    } else {
      currentPosition++;
    }
  }

  if (checkGamepadHold(0, DPadUp)) {
    integerArray[currentPosition] += 1;
    if (integerArray[currentPosition] > 9) {
      integerArray[currentPosition] = 0;
    }
  } else if (checkGamepadHold(0, DPadDown)) {
    integerArray[currentPosition] -= 1;
    if (integerArray[currentPosition] < 0) {
      integerArray[currentPosition] = 9;
    }
  }
}
