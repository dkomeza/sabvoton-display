#include "controller.h"

using namespace Controller_Private;

// Done
void Controller::init()
{
    controllerSerial.begin(baudRate, SERIAL_8N1, controllerRXPin, controllerTXPin);

    changeMode(data.mode);
}

// Done
void Controller::handle()
{
    // Prevent rollower
    if (millis() < lastUpdate)
        lastUpdate = millis();

    // Control update interval
    if (millis() - lastUpdate < receiveInterval)
        return;

    if (controllerSerial.available() > 4) // minimum packet size
        Packet packet(controllerSerial);
}

// Done
void Controller::changeMode(MODE mode)
{
    int bufferSize = 5;
    byte buffer[bufferSize];

    byte size = 2;
    byte type = (byte)PACKET_TYPE::CHANGE_MODE;

    buffer[0] = startByte;
    buffer[1] = size;
    buffer[2] = type;
    buffer[3] = (byte)mode;
    buffer[4] = calculateChecksum(buffer, bufferSize);

    controllerSerial.write(buffer, bufferSize);
}

// Done
void Controller::increaseGear()
{
    int bufferSize = 5;

    byte buffer[bufferSize];

    byte size = 2;
    byte type = (byte)PACKET_TYPE::GEAR_CONTROL;
    byte action = (byte)GEAR_CONTROL::INCREASE_GEAR;

    buffer[0] = startByte;
    buffer[1] = size;
    buffer[2] = type;
    buffer[3] = action;
    buffer[4] = calculateChecksum(buffer, bufferSize);

    controllerSerial.write(buffer, bufferSize);
}

// Done
void Controller::decreaseGear()
{
    int bufferSize = 5;

    byte buffer[bufferSize];

    byte size = 2;
    byte type = (byte)PACKET_TYPE::GEAR_CONTROL;
    byte action = (byte)GEAR_CONTROL::DECREASE_GEAR;

    buffer[0] = startByte;
    buffer[1] = size;
    buffer[2] = type;
    buffer[3] = action;
    buffer[4] = calculateChecksum(buffer, bufferSize);

    controllerSerial.write(buffer, bufferSize);
}

Packet::Packet(HardwareSerial &serial)
{
    while (serial.peek() != 65)
    {
        serial.read();
        if (serial.available() <= 0)
            return;
    }

    int startByte = serial.read();
    int size = serial.read();
    packet = {(byte)startByte, (byte)size};

    if (size < 1)
        return;

    for (int i = 0; i < size; i++)
    {
        packet.push_back(serial.read());
    }

    byte checksum = serial.read();
    packet.push_back(checksum);

    if (checksum != calculateChecksum(packet.data(), packet.size()))
    {
        packet.clear();
        return;
    }

    MODE mode = (MODE)packet[2];

    if (mode != data.mode)
    {
        packet.clear();
        return;
    }

    // Remove startByte, size, mode and checksum
    packet.erase(packet.begin(), packet.begin() + 3);
    packet.pop_back();

    switch (mode)
    {
    case MODE::MAIN:
        modeMain();
        break;
    case MODE::TORQUE:
        modeTorque();
        break;
    default:
        break;
    }

    packet.clear();
}

void Packet::modeMain()
{
    if (packet.size() != 7)
    {
        return;
    }

    MainData mainData;

    mainData.speed = packet[0];
    mainData.batteryVoltage = (packet[1] << 8) + packet[2];
    mainData.gear = packet[3];
    mainData.engineTemperature = int8_t(packet[4]);
    mainData.controllerTemperature = int8_t(packet[5]);
    mainData.batteryTemperature = int8_t(packet[6]);

    data.mainData = mainData;

    if (data.mode == MODE::MAIN)
        Screen::view_main.update();
}

void Packet::modeTorque()
{
    if (packet.size() != 4)
        return;

    TorqueData torqueData;

    torqueData.torque = packet[0];
    torqueData.gear = packet[1];
    torqueData.engineTemperature = packet[2];
    torqueData.controllerTemperature = packet[3];

    data.torqueData = torqueData;

    Screen::torque.update();
}
