#include <Arduino.h>

#include "connection/OTA.h"

#include "data/data.h"
#include "screen/screen.h"
#include "io/io.h"
#include "controller/controller.h"

Data data;
IO io;
Controller controller;

void setup()
{
    Serial.begin(115200);

    Screen::setup();
    controller.init();
    io.setup();

    OTA::setupOTA();
}

void loop()
{
    OTA::update();
    io.update();
    controller.handle();

    delay(1);
}
