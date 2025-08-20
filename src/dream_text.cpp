#include "SDL_surface.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <dream_text.h>
#include <dream_variables.h>
#include <iostream>
using namespace std;

void loadFontFromFile(char *path, Font *font, int ptSize) {
  TTF_Font *fontTtf = TTF_OpenFont(path, ptSize);

  if (fontTtf != nullptr) {
    font->fontTtf = fontTtf;
    font->fontPath = path;
    font->ptSize = ptSize;

    SDL_Surface *textSurface =
        TTF_RenderText_Solid(fontTtf, "W", {255, 255, 255});

    font->textSize = {0, 0, (float)textSurface->w, (float)textSurface->h};

    delete textSurface;
  } else {
    cerr << "Font Loading Failed" << endl;
  }
}

void changeFontSize(Font *font, int ptSize) {
  if (font->fontPath == nullptr) {
    cerr << "Font Path Empty" << endl;
    return;
  }

  if (ptSize == font->ptSize) {
    cerr << "The size is already set" << endl;
    return;
  }

  font->fontTtf = TTF_OpenFont(font->fontPath, ptSize);
}

void writeText(char *text, Vector2 pos, Color color, Font *font) {
  SDL_Color textColor = {color.r, color.g, color.b, color.a};

  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font->fontTtf, text, textColor);

  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);

  SDL_Rect textRect = {(int)pos.x, (int)pos.y, textSurface->w, textSurface->h};

  SDL_FreeSurface(textSurface);

  SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

void writeBlendedText(char *text, Vector2 pos, Color color, Font *font) {
  SDL_Color textColor = {color.r, color.g, color.b, color.a};

  SDL_Surface *textSurface =
      TTF_RenderText_Solid(font->fontTtf, text, textColor);

  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);
  SDL_SetTextureBlendMode(textTexture, SDL_BLENDMODE_MOD);

  SDL_Rect textRect = {(int)pos.x, (int)pos.y, textSurface->w, textSurface->h};

  SDL_FreeSurface(textSurface);

  SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}
