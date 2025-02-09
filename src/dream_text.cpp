#include <dream_text.h>
#include <iostream>
#include <dream_variables.h>
#include <SDL_ttf.h>
#include <SDL.h>
using namespace std;

void loadFontFromFile(char* path, Font* font, int ptSize){
  TTF_Font* fontTtf = TTF_OpenFont(path, ptSize);

  if(fontTtf != NULL){
    font->fontTtf = fontTtf;
    font->fontPath = path;
    font->ptSize = ptSize;
  } else {
    cerr << "Font Loading Failed" <<  endl;
  }
}

void changeFontSize(Font* font, int ptSize){
  if(font->fontPath == NULL){
    cerr << "Font Path Empty" << endl; 
    return;
  }

  if(ptSize == font->ptSize){
    cerr << "The size is already set" << endl;
    return;
  }

  font->fontTtf = TTF_OpenFont(font->fontPath, ptSize);
}

void writeText(char* text, Vector2 pos, Color color, Font* font){
   SDL_Color textColor = {color.r, color.g, color.b, color.a};

   SDL_Surface* textSurface = TTF_RenderText_Solid(font->fontTtf, text, textColor);

   SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

   SDL_Rect textRect = {(int)pos.x, (int)pos.y, textSurface->w, textSurface->h};

   SDL_FreeSurface(textSurface);

   SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}
