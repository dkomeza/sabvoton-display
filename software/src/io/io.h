#pragma once

#include <Arduino.h>
#include <button.h>

#include "data/data.h"
#include "screen/screen.h"
#include "controller/controller.h"

namespace IO_Private
{
    void buttonUpOnClick();
    void buttonDownOnClick();
    void buttonPowerOnClick();

    void buttonPowerOnDoubleClick();
}

class IO
{
private:
    long unsigned int lastUpdate = 0;
    int updateInterval = 20;

    const int BUTTON_DOWN_PIN = 12;
    const int BUTTON_POWER_PIN = 14;
    const int BUTTON_UP_PIN = 27;

    Button buttonUp = Button(BUTTON_UP_PIN);
    Button buttonDown = Button(BUTTON_DOWN_PIN);
    Button buttonPower = Button(BUTTON_POWER_PIN);

public:
    void setup();
    void update();
};

extern IO io;
