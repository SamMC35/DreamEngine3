#include <iostream>

#include <dream_main.h>
#include <dream_variables.h>

#include <SDL.h>
#include <SDL_render.h>
#include <SDL_gamecontroller.h>
#include <SDL_rect.h>
#include <SDL_ttf.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 28000

#define MAX_CHANNELS 4;
using namespace std;
//Add a list of screens along with their priority


SDL_Window* window;
SDL_Event event;

SDL_RendererInfo* info = nullptr;

SDL_Renderer* renderer = nullptr;

SDL_AudioDeviceID audio_device;

SDL_GameController* player1;

bool gCanQuit = false;

unsigned int resX = 0;
unsigned int resY = 0;

SoundData channels[4] = {0};

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

Uint32 frameStart;

void audio_callback(void *userdata, Uint8 *stream, int len);

bool initDreamEngine(char* window_name, int resX_arg, int resY_arg, bool fullscreen){
		bool success = false;

    resX = resX_arg;
    resY = resY_arg;

		//Start every subsystem
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
      TTF_Init();
      window = SDL_CreateWindow((char*) "Hello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_OPENGL);

      cout << "Window created: " << window << endl;

      if(window){
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        // cout << info->flags << endl;  
        if(renderer){
          // SDL_GetRendererInfo(renderer, info);
          cout << "Renderer Created:" << renderer << endl;
          success = true;
          //TODO: please change this later
          for(int i = 0; i < SDL_NumJoysticks(); i++){
            player1 = SDL_GameControllerOpen(i);
            cout << "Gamepad added: " << SDL_GameControllerName(player1) << endl;
          }

          SDL_AudioSpec spec = {0};
          spec.freq = SAMPLE_RATE;
          spec.format = AUDIO_S16SYS;
          spec.channels = 1;
          spec.samples = 2048;
          spec.callback = audio_callback;

          audio_device = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
          if (!audio_device) {
              cerr << "Error in creating audio device: " << SDL_GetError() << endl;
          }
          SDL_PauseAudioDevice(audio_device, 0); 

        } else {
          cerr << "Renderer failed to initialize" << SDL_GetError() << endl;
        }
      }

    } else {
      cerr << "SDL failed to initialize" << SDL_GetError() << endl;
    }
    
    //SDL_SetHint(SDL_HINT_RENDER_DRIVER, "metal");
		
    //
		//
		return success;	
}

bool checkQuit(){
  SDL_PollEvent(&event);

  if(event.type == SDL_QUIT){
    return true;
  }

  return gCanQuit;
}

void killGame(){
  gCanQuit = true;
}

void audio_callback(void *userdata, Uint8 *stream, int len) {
    int16_t *buffer = (int16_t *)stream;
    int samples = len / sizeof(int16_t);

    for (int i = 0; i < samples; i++) {
        int16_t mixed_sample = 0;
        Uint32 now = SDL_GetTicks();

        for (int ch = 0; ch < 4; ch++) {
            if (channels[ch].active && now < channels[ch].end_time) {
                int period = SAMPLE_RATE / channels[ch].frequency;
                mixed_sample += ((channels[ch].sample_count % period) < (period / 2) ? 1 : -1) * 4000;

                channels[ch].sample_count++;
            } else {
                channels[ch].active = 0; 
            }
        }

        buffer[i] = mixed_sample;
    }
}

bool collisionCheck(Vector2 a, Vector2 b){
  SDL_FRect* aRect = new SDL_FRect{a.x, a.y, a.w, a.h};
  SDL_FRect* bRect = new SDL_FRect{b.x, b.y, b.w, b.h};

  return SDL_HasIntersectionF(aRect, bRect);
}

void resetTimer(Timer* timer){
  timer->current_time = 0;
}

void incrementTimer(Timer* timer){
  timer->current_time++;
}

void setMaxTimer(Timer *timer, int time){
  timer->max_time = time;
}

void quitDreamEngine(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_CloseAudioDevice(audio_device);

  TTF_Quit();
  SDL_Quit();
}

void clearScreen(){
		// Clear everything
    frameStart = SDL_GetTicks();
    SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}


void render(){
		// Render the screens
    SDL_RenderPresent(renderer);

    Uint32 frameTime = SDL_GetTicks() - frameStart; 
    if (frameTime < FRAME_DELAY) {
        SDL_Delay(FRAME_DELAY - frameTime); 
    }
}
