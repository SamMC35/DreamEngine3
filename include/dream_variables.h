#ifndef VARIABLES_H
#define VARIABLES_H

#ifdef SDL_AudioDeviceID
#undef SDL_AudioDeviceID
#endif

#include <SDL.h>
#include <SDL_gamecontroller.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

extern SDL_Renderer* renderer;             //Single Renderer used by DreamEngine3
extern unsigned int scaleX, scaleY;        //scale X and Y sizes based on resolutions
extern unsigned int resX, resY;           //Resolution of the game
extern SDL_GameController* player1;
extern SDL_AudioDeviceID audio_device;



//Vector2 to represent 2D position and size
typedef struct Vector2{
  float x, y, w, h;
}Vector2;

typedef struct {
    float frequency;
    int sample_count;
    int duration_samples;
    int active;
    Uint32 end_time;
} SoundData;

extern SoundData channels[4];



//Color data
typedef struct Color{
  Uint8 r, g, b, a;
}Color;

typedef struct Font{
  TTF_Font* fontTtf;
  int ptSize;
  char* fontPath;
}Font;

typedef struct Timer{
  int max_time;
  int current_time;
  bool active;
}Timer;

#endif 
