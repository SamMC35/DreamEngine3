#include <iostream>
#include <dream_main.h>
#include <dream_graphics.h>
#include <dream_variables.h>
#include <dream_gamepad.h>
#include <dream_text.h>

using namespace std;

int main(){
  if(initDreamEngine((char*) "Test", 800, 600, false)){
    Sprite* sprite = new Sprite();

    Font* font = new Font();
    loadFontFromFile((char*)"8bit.ttf", font, 16);  


    Vector2 pos = {10, 10, 64, 64};
    Color color = {255, 255, 255, 255};

    sprite->pos = pos;
    sprite->color = color;
    while(!checkQuit()){
      clearScreen();

      pos = sprite->pos;

      if(checkGamepadPress(0, DPadLeft)){
        pos.x -= 2;
      } 

      if(checkGamepadPress(0, DPadRight)){
        pos.x += 2;
      }

      cout << "Analog:" << checkGamepadAnalog(0, LeftStickX) << endl;

      pos.x += (checkGamepadAnalog(0, LeftStickX) / 32767) * 4;

      if(checkGamepadPress(0, A)){
       rumbleGamepad(0, 6000,6000,1000);
      }

      sprite->pos = pos;
      
      writeText((char*) "FUCK YOU", {0, 0, 0, 0}, color, font);

      drawRectangle(sprite);     

      render();
    }


    quitDreamEngine();
  } else {
    cout << "Failed to Initialize Dream Engine" << endl;
  }

}
