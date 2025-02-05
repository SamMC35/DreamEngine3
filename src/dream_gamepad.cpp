#include<dream_gamepad.h>
#include<SDL.h>
#include<SDL_gamecontroller.h>
#include<iostream>
#include<dream_variables.h>

using namespace std;

SDL_GameControllerButton getValue(ControllerButton button){
  return static_cast<SDL_GameControllerButton>(button);
}

bool checkGamepadPress(int joystick_index, ControllerButton button){
    //cout << "Checking for button press: " << button <<endl; 
    return SDL_GameControllerGetButton(player1, getValue(button));
}

void checkGamepadAnalog(int joystick_index, ControllerAxis axis){
  
}

void rumbleGamepad(int joystick_index, Uint16 left_motor, Uint16 right_motor, Uint32 duration){
  cout << "Rumble support: " << SDL_GameControllerHasRumble(player1)<< endl;
  SDL_GameControllerRumble(player1, left_motor, right_motor, duration);  
}
