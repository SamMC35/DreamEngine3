#ifndef TEXT_H
#define TEXT_H

#include "dream_variables.h"

void writeText(char*, Vector2, Color, Font*);
void loadFontFromFile(char*, Font*, int);
void changeFontSize(Font*, int);
void writeBlendedText(char*, Vector2, Color, Font*);

#endif

