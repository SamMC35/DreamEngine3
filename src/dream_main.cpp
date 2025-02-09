#include <iostream>

#include <dream_main.h>
#include <dream_variables.h>

#include <SDL.h>
#include <SDL_render.h>
#include <SDL_gamecontroller.h>
#include <SDL_rect.h>
using namespace std;
//Add a list of screens along with their priority


SDL_Window* window;
SDL_Event event;

SDL_RendererInfo* info = nullptr;

SDL_Renderer* renderer = nullptr;

SDL_GameController* player1;

unsigned int resX = 0;
unsigned int resY = 0;

bool initDreamEngine(char* window_name, int resX_arg, int resY_arg, bool fullscreen){
		bool success = false;

    resX = resX_arg;
    resY = resY_arg;

		//Start every subsystem
		if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
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

  return false;
}

bool collisionCheck(Vector2 a, Vector2 b){
  SDL_FRect* aRect = new SDL_FRect{a.x, a.y, a.w, a.h};
  SDL_FRect* bRect = new SDL_FRect{b.x, b.y, b.w, b.h};

  return SDL_HasIntersectionF(aRect, bRect);
}

void quitDreamEngine(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

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
