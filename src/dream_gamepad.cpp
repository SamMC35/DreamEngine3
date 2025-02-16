#include<dream_gamepad.h>
#include<SDL.h>
#include<SDL_gamecontroller.h>
#include<iostream>
#include<unordered_map>
#include<dream_variables.h>
#include<cmath>

#define DEADZONE 8000

using namespace std;

unordered_map<int, bool> joyState;

SDL_GameControllerButton getValue(ControllerButton button){
  return static_cast<SDL_GameControllerButton>(button);
}

SDL_GameControllerAxis getAxisValue(ControllerAxis axis){
  return static_cast<SDL_GameControllerAxis>(axis);
}

bool checkGamepadPress(int joystick_index, ControllerButton button){
    //cout << "Checking for button press: " << button <<endl; 
    return SDL_GameControllerGetButton(player1, getValue(button));
}

bool checkGamepadHold(int joystick_index, ControllerButton button){
    bool canPress = checkGamepadPress(joystick_index, button);

    if(canPress && !joyState[button]){
      joyState[button] = true;
      return true;
    } 

    if(!canPress){
      joyState[button] = false;
    }

    return false;
}

float checkGamepadAnalog(int joystick_index, ControllerAxis axis){
    float axisValue = SDL_GameControllerGetAxis(player1, getAxisValue(axis));

    return abs(axisValue) > DEADZONE? axisValue : 0;
}

void rumbleGamepad(int joystick_index, Uint16 left_motor, Uint16 right_motor, Uint32 duration){
  cout << "Rumble support: " << SDL_GameControllerHasRumble(player1)<< endl;
  SDL_GameControllerRumble(player1, left_motor, right_motor, duration);  
}
