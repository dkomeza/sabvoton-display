#pragma once

#include <Arduino.h>
#include <array>

#include "data/data.h"
#include "screen/tft.h"

class Torque
{
public:
    Torque();

    void draw();
    void update();

private:
    std::array<int, 200> torqueArray;
    int gear = -1;
    int engineTemperature = -1;
    int controllerTemperature = -1;

    void drawChart();
    void drawGear();
    void drawEngineTemperature();
    void drawControllerTemperature();
};

extern Torque torque;
