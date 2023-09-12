#pragma once

#include <Arduino.h>
#include <array>

#include "controller/communication.h"

using namespace Communication;

class Data
{
public:
    // Screen
    MODE mode = MODE::MAIN;

    // Main
    MainData mainData;

    // Torque
    TorqueData torqueData;
};

extern Data data;