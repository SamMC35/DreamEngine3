#include <iostream>

#include <dream_graphics.h>
#include <dream_variables.h>

#include <SDL.h>


void setColor(Color color){
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

//Draws a rectangle
void drawRectangle(Sprite* sprite){
  setColor(sprite->color);
  Vector2 pos = sprite->pos;
  SDL_Rect* rect = new SDL_Rect{(int)pos.x, (int)pos.y, (int)pos.w, (int)pos.h};
  // cout << rect->x << endl;
  // cout << "Renderer Inside Graphics:" << renderer << endl;
  SDL_RenderFillRect(renderer, rect);
}

//Draw a line
void drawLine(Sprite* sprite){
  //x,y act as x1, y1 and w and h act as x2 and y2
  setColor(sprite->color);
  Vector2 pos = sprite->pos;
  SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.w, pos.h);
}

//Draw a pixel
void drawPixel(Sprite* sprite){
  setColor(sprite->color);
  Vector2 pos = sprite->pos;
  SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

void drawBlendRectangle(Sprite* sprite){
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_MOD);
  drawRectangle(sprite);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}
