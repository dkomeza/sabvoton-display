#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "data/data.h"

#include "screen/menu/menu.h"
#include "screen/main/main.h"
#include "screen/torque/torque.h"
#include "screen/settings/settings.h"

namespace Screen
{
    void setup();
    void changeView();
    void drawPacket(byte buffer[], int size);

    // Modules
    extern Menu menu;
    extern Main view_main;
    extern Torque torque;
    extern Settings settings;
}