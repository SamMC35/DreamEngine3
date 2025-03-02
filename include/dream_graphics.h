#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include "dream_variables.h"

typedef struct Sprite{

    SDL_Texture* texture;
    Vector2 pos;
    Color color;

    int scaleX, scaleY;
} Sprite;

void drawRectangle(Sprite*);
void drawLine(Sprite*);
void drawPixel(Sprite*);
void drawBlendRectangle(Sprite*);

void loadTexture(Sprite*, char*);

void scaleTexture(Sprite*, Vector2);

void renderTexture(Sprite*);
void renderTextureCropped(Sprite*, Vector2);

#endif 
