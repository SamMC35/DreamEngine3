#include <dream_gamepad.h>
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <dream_variables.h>

#define DEADZONE 8000

using namespace std;

  // Global joystick object
unordered_map<int, bool> joyState;

void printJoystickState() {
    int numButtons = SDL_JoystickNumButtons(player1);
    int numAxes = SDL_JoystickNumAxes(player1);
    int numHats = SDL_JoystickNumHats(player1);

    std::cout << "=== Joystick State ===" << std::endl;

    // Buttons
    for (int i = 0; i < numButtons; ++i) {
        Uint8 state = SDL_JoystickGetButton(player1, i);
        if (state) {
            std::cout << "Button " << i << " pressed" << std::endl;
        }
    }

    // Axes
    for (int i = 0; i < numAxes; ++i) {
        Sint16 value = SDL_JoystickGetAxis(player1, i);
        if (abs(value) > 8000) {  // Deadzone filter
            std::cout << "Axis " << i << " moved: " << value << std::endl;
        }
    }

    // Hats (D-pad)
    for (int i = 0; i < numHats; ++i) {
        Uint8 hat = SDL_JoystickGetHat(player1, i);
        if (hat != SDL_HAT_CENTERED) {
            std::cout << "Hat " << i << " direction: ";
            if (hat & SDL_HAT_UP) std::cout << "UP ";
            if (hat & SDL_HAT_DOWN) std::cout << "DOWN ";
            if (hat & SDL_HAT_LEFT) std::cout << "LEFT ";
            if (hat & SDL_HAT_RIGHT) std::cout << "RIGHT ";
            std::cout << std::endl;
        }
    }
}

// You need to manually map enums to joystick buttons/axes
int getButtonIndex(ControllerButton button) {
    switch (button) {
        case A: return 0;
        case B: return 1;
        case X: return 2;
        case Y: return 3;
        case DPadUp: return 4;
        case DPadDown: return 5;
        case DPadLeft: return 6;
        case DPadRight: return 7;
        case L: return 8;
        case R: return 9;
  
        case START: return 12;
        case LeftStick: return 13;
        case RightStick: return 14;
        default: return -1;
    }
}

int getAxisIndex(ControllerAxis axis) {
    switch (axis) {
        case LeftStickX: return 0;
        case LeftStickY: return 1;
        case RightStickX: return 2;
        case RightStickY: return 3;
        case LeftTrigger: return 4;
        case RightTrigger: return 5;
        default: return -1;
    }
}

bool checkGamepadPress(int joystick_index, ControllerButton button) {
    int index = getButtonIndex(button);
    return index >= 0 ? SDL_JoystickGetButton(player1, index) : false;
}

bool checkGamepadHold(int joystick_index, ControllerButton button) {
    bool canPress = checkGamepadPress(joystick_index, button);

    if (canPress && !joyState[button]) {
        joyState[button] = true;
        return true;
    }

    if (!canPress) {
        joyState[button] = false;
    }

    return false;
}

float checkGamepadAnalog(int joystick_index, ControllerAxis axis) {
    int index = getAxisIndex(axis);
    Sint16 value = SDL_JoystickGetAxis(player1, index);
    return abs(value) > DEADZONE ? value : 0;
}

void clearInputs() {
    SDL_PumpEvents();
}

bool isDPadPressed(ControllerButton btn) {
    Uint8 hat = SDL_JoystickGetHat(player1, 0); // Assume one hat

    switch (btn) {
        case DPadUp: return hat & SDL_HAT_UP;
        case DPadDown: return hat & SDL_HAT_DOWN;
        case DPadLeft: return hat & SDL_HAT_LEFT;
        case DPadRight: return hat & SDL_HAT_RIGHT;
        default: return false;
    }
}

bool isDPadHeld(ControllerButton btn) {
    bool canPress = isDPadPressed(btn);

    if (canPress && !joyState[btn]) {
        joyState[btn] = true;
        return true;
    }

    if (!canPress) {
        joyState[btn] = false;
    }

    return false;
}


bool isAnyButtonPressed() {
    int numButtons = SDL_JoystickNumButtons(player1);
    for (int i = 0; i < numButtons; ++i) {
        if (SDL_JoystickGetButton(player1, i)) {
            return true;
        }
    }
    return false;
}

bool checkAnyGamepadPress() {
    return checkGamepadPress(0, A) || checkGamepadPress(0, B) || checkGamepadPress(0, START);
}


