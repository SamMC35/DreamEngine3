#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include "dream_variables.h"

class Sprite{
private:
    SDL_Texture* texture;
    Vector2 pos;
    Color color;
  
public:
    //void addTexture(char*);
    //SDL_Texture* getTexture();

    void setPos(Vector2);
    Vector2 getPos();

    void setColor(Color);
    Color getColor();
};

void drawRectangle(Sprite*);
void drawLine(Sprite*);
void drawPixel(Sprite*);

#endif // !DEBUG
