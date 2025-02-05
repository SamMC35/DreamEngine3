#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <SDL_gamecontroller.h>

typedef enum ControllerButton{

        A = SDL_CONTROLLER_BUTTON_A,          // Right face button
        B = SDL_CONTROLLER_BUTTON_B,          // Bottom face button
        X = SDL_CONTROLLER_BUTTON_X,          // Top face button
        Y = SDL_CONTROLLER_BUTTON_Y,          // Left face button

        // Directional buttons (D-pad)
        DPadUp = SDL_CONTROLLER_BUTTON_DPAD_UP,     // Up on the D-pad
        DPadDown = SDL_CONTROLLER_BUTTON_DPAD_DOWN,   // Down on the D-pad
        DPadLeft = SDL_CONTROLLER_BUTTON_DPAD_LEFT,   // Left on the D-pad
        DPadRight = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,  // Right on the D-pad

        // Shoulder buttons
        L = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,          // Left bumper
        R = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,          // Right bumper
        ZL,         // Left trigger
        ZR,         // Right trigger

        // Analog stick buttons
        LeftStick,  // Pressing down on the left analog stick
        RightStick  // Pressing down on the right analog stick 

}ControllerButton;

typedef enum ControllerAxis{
      LeftStickX,       // Left axis X
      LeftStickY,       // Left axis Y
      RightStickX,      // Right axis X 
      RightStickY,       // Right axis Y 
      LeftTrigger,      // Left Trigger Axis(Not for Nintendo Switch)
      RightTrigger      // Right Trigger Axis(Not for Nintendo Switch)
}ControllerAxis;

bool checkGamepadPress(int joystick_index, ControllerButton button);
void checkGamepadAnalog(int joystick_index, ControllerAxis axis);
void rumbleGamepad(int joystick_index, Uint16 left_motor, Uint16 right_motor, Uint32 duration);

#endif // !GAMEPAD_H

