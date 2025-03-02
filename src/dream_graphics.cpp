#include <iostream>

#include <dream_graphics.h>
#include <dream_variables.h>

#include <SDL.h>
#include <SDL_image.h>


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

//Loads a Texture
void loadTexture(Sprite* sprite, char* path){
  SDL_Surface* temp = IMG_Load(path);

  if(!temp){
    cerr << "Failed to Load Image" << IMG_GetError() << endl;
    return;
  }

  sprite->pos.w = temp->w;
  sprite->pos.h = temp->h;

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temp);

  if(!texture){
    cerr << "Failed to create Texture: " << SDL_GetError() << endl;
    return;
  }

  sprite->texture = texture;

  SDL_FreeSurface(temp);
}

//Renders a texture
void renderTexture(Sprite* sprite){
  Vector2 pos = sprite->pos;
  SDL_Rect rect = {(int)pos.x, (int)pos.y, (int)pos.w, (int)pos.w};

  SDL_RenderCopy(renderer, sprite->texture, NULL, &rect);
}

void renderTextureCropped(Sprite* sprite, Vector2 cropPos){
  SDL_Rect cropRect = {(int)cropPos.x, (int)cropPos.y, (int)cropPos.w, (int)cropPos.h};

  Vector2 pos = sprite->pos;
  SDL_Rect rect = {(int)pos.x, (int)pos.y, (int)pos.w, (int)pos.w};

  SDL_RenderCopy(renderer, sprite->texture, &cropRect, &rect);  
}