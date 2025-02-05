#include <iostream>

#include <dream_graphics.h>
#include <dream_variables.h>

#include <SDL.h>


Vector2 Sprite::getPos(){
  return pos;
}

Color Sprite::getColor(){
  return color;
}

void Sprite::setColor(Color color){
  this->color = color;
}

void Sprite::setPos(Vector2 pos){
  this->pos = pos;
}

void setColor(Color color){
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

//Draws a rectangle
void drawRectangle(Sprite* sprite){
  setColor(sprite->getColor());
  Vector2 pos = sprite->getPos();
  SDL_Rect* rect = new SDL_Rect{pos.x, pos.y, pos.w, pos.h};
  // cout << rect->x << endl;
  // cout << "Renderer Inside Graphics:" << renderer << endl;
  SDL_RenderFillRect(renderer, rect);
}

//Draw a line
void drawLine(Sprite* sprite){
  //x,y act as x1, y1 and w and h act as x2 and y2
  setColor(sprite->getColor());
  Vector2 pos = sprite->getPos();
  SDL_RenderDrawLine(renderer, pos.x, pos.y, pos.w, pos.h);
}

//Draw a pixel
void drawPixel(Sprite* sprite){
  setColor(sprite->getColor());
  Vector2 pos = sprite->getPos();
  SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}


