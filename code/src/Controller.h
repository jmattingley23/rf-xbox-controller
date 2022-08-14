#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ControllerData.h"
#include <Arduino.h>

class Controller {

public:
    Controller();
    ~Controller();

    /**
     * Updates the internal class state to represent the controller inputs. Also
     * performs any necessary scaling or remapping
     */
    void gatherAllInputs();

    /**
     * Provides voltage to the two rumble motors based on the trigger positions.
     */
    void doRumbleMotors();

    /**
     * Get's the current state of the controller as a minified
     * data structure for transmission
     * 
     * @return A ControllerDataStruct representing the current controller inputs
     */
    ControllerData::ControllerDataStruct getStruct();

private:
    ControllerData::ControllerDataStruct data;

    // internal state variables
    byte leftBumper;
    byte rightBumper;
    byte start;
    byte select;
    byte capture;
    byte a;
    byte b;
    byte x;
    byte y;
    int leftTrigger;
    int rightTrigger;
    byte dpadUp;
    byte dpadDown;
    byte dpadLeft;
    byte dpadRight;
    int leftStickX;
    int leftStickY;
    int rightStickX;
    int rightStickY;

    // constants to help account for mechanical limits
    const int LEFT_TRIGGER_MIN = 526;
    const int LEFT_TRIGGER_MAX = 467;
    const int RIGHT_TRIGGER_MIN = 526;
    const int RIGHT_TRIGGER_MAX = 481;
    const int JOYSTICK_DEADZONE = 30;
    const long JOYSTICK_CURVE_MAX = 512L * 512L;
    const byte RUMBLE_MIN = 35;
    const byte RUMBLE_MAX = 70;

    // physical controller pinout
    const byte PIN_LEFT_X = A7;
    const byte PIN_LEFT_Y = A6;
    const byte PIN_RIGHT_X = A0;
    const byte PIN_RIGHT_Y = A1;
    const byte PIN_LEFT_TRIGGER = A8;
    const byte PIN_RIGHT_TRIGGER = A10;
    const byte PIN_B_BUTTON = 1;
    const byte PIN_AXY_BUTTONS = A3;
    const byte PIN_START_BUTTONS = A2;
    const byte PIN_DPAD = A5;
    const byte PIN_BUMPERS = A4;


    /**
     * Takes raw analog joystick values and cleans them up
     * 
     * This function will re-center stick values to compensate for mechanical imperfections, as well
     * remap the values to a smoother curve and introduce a small deadzone in the center
     * 
     * @param value The raw axis value read from the pin in the range 0 to 1023
     * @param centerpoint The value read from the pin when the thumbstick is in a neutral position
     * @param min The lowest value the joystick can reach, usually 0 barring any mechanical constraints
     * @param max The highest value the joystick can reach, usually 1023 barring any mechanical contraints
     * @return A mapped, centered thumbstick value in the range -255 to 255
     */
    int mapJoystick(int value, int centerpoint, int min=0, int max=1023);

    /**
     * Takes the internal class variables and packs them into a minimal struct for transmission.
     * 
     * This functions minimizes using bit level operations to make the struct
     * as small as possible.
     */
    void packageStruct();

};

#endif
