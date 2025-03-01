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

SoundData sound = {440, 0, 50, 0};

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
          spec.userdata = &sound;

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
        if (sound.active && sound.sample_count < sound.duration_samples) {
            
            int period = SAMPLE_RATE / sound.frequency;
            buffer[i] = ((sound.sample_count % period) < (period / 2) ? 1 : -1) * 8000;

            sound.sample_count++;

            if (SDL_GetTicks() >= sound.end_time) {
                sound.active = 0;
            }
        } else {
            buffer[i] = 0; 
        }
    }

    if (sound.sample_count >= sound.duration_samples) {
        sound.active = 0;
    }
}

bool collisionCheck(Vector2 a, Vector2 b){
  SDL_FRect* aRect = new SDL_FRect{a.x, a.y, a.w, a.h};
  SDL_FRect* bRect = new SDL_FRect{b.x, b.y, b.w, b.h};

  return SDL_HasIntersectionF(aRect, bRect);
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
    SDL_SetRenderDrawColor(renderer, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}


void render(){
		// Render the screens
    SDL_RenderPresent(renderer);
}
