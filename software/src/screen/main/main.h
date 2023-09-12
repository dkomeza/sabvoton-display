#pragma once

#include <Arduino.h>

#include "data/data.h"

#include "screen/tft.h"

class Main
{
public:
    Main(){};

    void draw();
    void update();

private:
    // Variables to keep track of the previous values
    int batteryVoltage = -1;
    int speed = -1;
    int gear = -1;
    int engineTemperature = -1;
    int controllerTemperature = -1;
    int batteryTemperature = -1;

    void drawBatteryVoltage();
    void drawBatteryTemperature();
    void drawSpeed();
    void drawGear();
    void drawEngineTemperature();
    void drawControllerTemperature();
};

extern Main view_main;