#ifndef COLORS_H
#define COLORS_H

#include "Arduino.h"

class Colors {
public:
    static Colors& getInstance() {
        static Colors INSTANCE;
        return INSTANCE;
    }

    const byte WHITE[3] = {255, 255, 255};
    const byte RED[3] = {255, 25, 0};
    const byte GREEN[3] = {25, 255, 25};
    const byte OFF[3] = {0, 0, 0};

private:
    Colors() {}

};

#endif
