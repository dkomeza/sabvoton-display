#pragma once

#include <Arduino.h>
#include <HardwareSerial.h>
#include <vector>

#include "communication.h"
#include "data/data.h"
#include "screen/screen.h"

namespace Controller_Private
{
    class Packet
    {
    public:
        Packet(HardwareSerial &serial);

    private:
        std::vector<byte> packet;

        void modeMain();
        void modeTorque();
        void modeSettings();
        void modeData();
    };
}

class Controller
{
public:
    void init();
    void handle();

    void changeMode(MODE mode);

    void increaseGear();
    void decreaseGear();

    void setBrake(bool brake);

private:
    const int controllerRXPin = 16;
    const int controllerTXPin = 17;

    HardwareSerial controllerSerial = HardwareSerial(2);

    long unsigned int lastUpdate = 0;
    int receiveInterval = 500;
};

extern Controller controller;
