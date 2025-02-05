#include <iostream>
#include <dream_main.h>
#include <dream_graphics.h>
#include <dream_variables.h>
#include <dream_gamepad.h>

using namespace std;

int main(){
  if(initDreamEngine((char*) "Test", 800, 600, false)){
    Sprite* sprite = new Sprite();

    Vector2 pos = {10, 10, 64, 64};
    Color color = {255, 255, 255, 255};

    sprite->setPos(pos);
    sprite->setColor(color);
    while(!checkQuit()){
      clearScreen();

      pos = sprite->getPos();

      if(checkGamepadPress(0, DPadLeft)){
        pos.x -= 2;
      } 

      if(checkGamepadPress(0, DPadRight)){
        pos.x += 2;
      }

      if(checkGamepadPress(0, A)){
       rumbleGamepad(0, 6000,6000,1000);
      }

      sprite->setPos(pos);
        

      drawRectangle(sprite);     

      render();
    }


    quitDreamEngine();
  } else {
    cout << "Failed to Initialize Dream Engine" << endl;
  }

}
