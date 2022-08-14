#ifndef CONTROLLER_DATA_H
#define CONTROLLER_DATA_H

#include <Arduino.h>

class ControllerData {

public:

    struct ControllerDataStruct {
        int16_t leftTrigger;
        int16_t rightTrigger;
        int16_t leftX;
        int16_t leftY;
        int16_t rightX;
        int16_t rightY;
        // byte buttons;

        String toString() {
            return String(leftTrigger + String(" ")
                + rightTrigger + String(" ")
                + leftX + String(" ")
                + leftY + String(" ")
                + rightX + String(" ")
                + rightY + String(" "));
                // + String(buttons, BIN));
        }
    };
    
};

#endif

