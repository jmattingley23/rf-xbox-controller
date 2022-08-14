#include "Controller.h"

Controller::Controller() {
    leftBumper = 0;
    rightBumper = 0;

    // pinMode(PIN_START, INPUT_PULLUP);
}

Controller::~Controller() {}

void Controller::gatherAllInputs() {
    // // bumpers are on A6 & A7 which are analogRead only, so we need to map to a binary value
    // leftBumper = map(analogRead(PIN_LEFT_BUMPER), 0, 1023, 0, 1);
    // rightBumper = map(analogRead(PIN_RIGHT_BUMPER), 0, 1023, 0, 1);

    // // start button uses carbon pads to short pullup resistor to ground, so we need to flip the value
    // start = map(digitalRead(PIN_START), 0, 1, 1, 0);

    // // triggers use hall-effect sensors, so we need to contrain them to a min & max range and then map to a clean 0-255
    // leftTrigger = constrain(analogRead(PIN_LEFT_TRIGGER), LEFT_TRIGGER_MAX, LEFT_TRIGGER_MIN);
    // leftTrigger = constrain(map(leftTrigger, LEFT_TRIGGER_MIN, LEFT_TRIGGER_MAX, 0, 255), 0, 255);
    // rightTrigger = constrain(analogRead(PIN_RIGHT_TRIGGER), RIGHT_TRIGGER_MAX, RIGHT_TRIGGER_MIN);
    // rightTrigger = constrain(map(rightTrigger, RIGHT_TRIGGER_MIN, RIGHT_TRIGGER_MAX, 0, 255), 0, 255);
    leftTrigger = analogRead(PIN_LEFT_TRIGGER);
    rightTrigger = analogRead(PIN_RIGHT_TRIGGER);

    // dpadUp = digitalRead(PIN_DPAD_UP);
    // dpadDown = digitalRead(PIN_DPAD_DOWN);
    // dpadLeft = digitalRead(PIN_DPAD_LEFT);
    // dpadRight = digitalRead(PIN_DPAD_RIGHT);

    leftStickX = mapJoystick(analogRead(PIN_LEFT_X), 539);
    leftStickY = mapJoystick(analogRead(PIN_LEFT_Y), 552, 27, 1023);
    rightStickX = mapJoystick(analogRead(PIN_RIGHT_X), 550);
    rightStickY = mapJoystick(analogRead(PIN_RIGHT_Y), 553);

    b = digitalRead(PIN_B_BUTTON);

    Serial.println(analogRead(PIN_START_BUTTONS));
}

ControllerData::ControllerDataStruct Controller::getStruct() {
    packageStruct();
    return data;
}

int Controller::mapJoystick(int value, int centerpoint, int min, int max) {
    // value = constrain(value, 0, 1023);
    // // remap the centerpoint and accomdate for a slight dead zone
    // if(value < (centerpoint - JOYSTICK_DEADZONE)) {
    //     value = map(constrain(value, min, 512), min, 512, -512, 0);
    // } else if(value > (centerpoint + JOYSTICK_DEADZONE)) {
    //     value = map(constrain(value, 512, max), 512, max, 0, 512);
    // } else {
    //     value = 0;
    // }
    // long curveMap = value;
    // // square and then linearly map to get a smoother curve
    // curveMap = curveMap * abs(curveMap); // use abs to preserve negative amplitude
    // value = map(curveMap, (-1L * JOYSTICK_CURVE_MAX), JOYSTICK_CURVE_MAX, 255, -255);
    return value;
}

void Controller::doRumbleMotors() {
    // byte triggerPosition = max(leftTrigger, rightTrigger);
    // byte vibration = map(triggerPosition, 0, 255, RUMBLE_MIN, RUMBLE_MAX);
    // if(vibration == RUMBLE_MIN) {
    //     vibration = 0;
    // }
    // analogWrite(PIN_VIBRATION, vibration);
}

void Controller::packageStruct() {
    data.leftTrigger = leftTrigger;
    data.rightTrigger = rightTrigger;
    data.leftX = leftStickX;
    data.leftY = leftStickY;
    data.rightX = rightStickX;
    data.rightY = rightStickY;

    // byte buttons[7] = {
    //                     leftBumper,
    //                     rightBumper,
    //                     start,
    //                     dpadUp,
    //                     dpadDown,
    //                     dpadLeft,
    //                     dpadRight
    //                 };

    // String buttonsBinary = "0";
    // for(byte i = 0; i < 7; i++) {
    //     buttonsBinary = String(buttonsBinary + (buttons[i] ? "1" : "0"));
    // }
    // data.buttons = strtol(buttonsBinary.c_str(), NULL, 2);
}
