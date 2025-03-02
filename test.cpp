#include <iostream>
#include <dream_main.h>
#include <dream_graphics.h>
#include <dream_variables.h>
#include <dream_gamepad.h>
#include <dream_text.h>
#include <dream_sound.h>

using namespace std;

int main(){
  if(initDreamEngine((char*) "Test", 800, 600, false)){
    Sprite* sprite = new Sprite();

    Font* font = new Font();
    loadFontFromFile((char*)"8bit.ttf", font, 16);  

    loadTexture(sprite, (char*)"green.png");


    Vector2 pos = {10, 10, 64, 64};
    Color color = {255, 255, 255, 255};

    sprite->pos.x = pos.x;
    sprite->pos.y = pos.y;

    sprite->color = color;
    while(!checkQuit()){
      clearScreen();

      renderTextureCropped(sprite, {0,0,12,12});   

      render();
    }

    delete sprite;
    delete font;

    quitDreamEngine();
  } else {
    cout << "Failed to Initialize Dream Engine" << endl;
  }

}
