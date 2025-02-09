#include<dream_gamepad.h>
#include<SDL.h>
#include<SDL_gamecontroller.h>
#include<iostream>
#include<dream_variables.h>
#include<cmath>

#define DEADZONE 8000

using namespace std;

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

float checkGamepadAnalog(int joystick_index, ControllerAxis axis){
    float axisValue = SDL_GameControllerGetAxis(player1, getAxisValue(axis));

    return abs(axisValue) > DEADZONE? axisValue : 0;
}

void rumbleGamepad(int joystick_index, Uint16 left_motor, Uint16 right_motor, Uint32 duration){
  cout << "Rumble support: " << SDL_GameControllerHasRumble(player1)<< endl;
  SDL_GameControllerRumble(player1, left_motor, right_motor, duration);  
}
