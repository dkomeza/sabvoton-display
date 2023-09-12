#include "main.h"
using namespace TFT;

// Main::Main()
// {
// }

void Main::draw()
{
    // Clear variables
    batteryVoltage = -1;
    speed = -1;
    gear = -1;
    engineTemperature = -1;
    controllerTemperature = -1;
    batteryTemperature = -1;

    // Clear screen
    tft.clearScreen();

    // Draw dividers
    tft.drawDivider(44);
    tft.drawDivider(SCREEN_HEIGHT - 45);

    // // Draw background
    // tft.fillRect(0, 0, SCREEN_WIDTH, 44, COLOR_GRAY);
    // tft.fillRect(0, SCREEN_HEIGHT - 44, SCREEN_WIDTH, 44, COLOR_GRAY);

    // Draw componentsp
    drawSpeed();
    drawBatteryVoltage();
    drawBatteryTemperature();
    drawGear();
    drawEngineTemperature();
    drawControllerTemperature();
}

void Main::update()
{
    drawSpeed();
    drawBatteryVoltage();
    drawBatteryTemperature();
    drawGear();
    drawEngineTemperature();
    drawControllerTemperature();
}

void Main::drawSpeed()
{
    if (speed == data.mainData.speed)
        return;

    // Check for out of bounds values
    if (speed > 99)
        speed = 99;

    if (speed < 0)
        speed = 0;

    // Create string
    String speedString = String(speed);
    if (speedString.length() == 1)
        speedString = "0" + speedString;

    // Handle exceptions
    if (speedString.length() > 2)
        return;

    tft.loadFont(FONT_164);

    // Draw speed
    int textWidth = tft.textWidth("00");
    tft.setTextPadding(textWidth);

    // String position
    int x = SCREEN_WIDTH / 2 - textWidth / 2;
    int y = SCREEN_HEIGHT / 2 - 24;

    tft.setTextDatum(ML_DATUM);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK, true);
    tft.drawString(speedString, x, y);

    tft.unloadFont();

    speed = data.mainData.speed;
}

void Main::drawBatteryVoltage()
{
    if (batteryVoltage == data.mainData.batteryVoltage)
        return;

    tft.loadFont(FONT_28);

    double voltage = data.mainData.batteryVoltage / 10.0;

    String batteryVoltageString = String(voltage, 1) + "V";

    if (batteryVoltageString.length() == 4)
        batteryVoltageString = "0" + batteryVoltageString;

    // if (batteryVoltageString.length() > 5)
    //     return;

    int textWidth = tft.textWidth("00.0V");

    tft.setTextPadding(textWidth);
    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(COLOR_GREEN, COLOR_BLACK, true);

    int x = 16;
    int y = 8;

    tft.drawString(batteryVoltageString, x, y);

    tft.unloadFont();

    batteryVoltage = data.mainData.batteryVoltage;
};

void Main::drawBatteryTemperature()
{
    if (batteryTemperature == data.mainData.batteryTemperature)
        return;

    int temperature = data.mainData.batteryTemperature;

    if (temperature < -99)
        temperature = -99;

    tft.loadFont(FONT_28);

    String batteryTemperatureString = String(temperature) + "°C";
    Color color = COLOR_GREEN;

    if (temperature < 0)
    {
        if (batteryTemperatureString.length() > 5)
            return;
    }
    else
    {
        if (batteryTemperatureString.length() > 5)
            return;
    }

    // Set color
    if (temperature < 10)
    {
        color = COLOR_BLUE;
    }
    else if (temperature < 26)
    {
        color = COLOR_GREEN;
    }
    else if (temperature < 50)
    {
        color = COLOR_YELLOW;
    }
    else
    {
        color = COLOR_RED;
    }

    int textWidth = tft.textWidth("000°C"); // Max length

    int x = SCREEN_WIDTH - 8 - textWidth;
    int y = 8;

    tft.setTextPadding(textWidth);
    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(color, COLOR_BLACK, true);

    tft.drawString(batteryTemperatureString, x, y);

    int padding = tft.textWidth("B: ");
    tft.setTextPadding(padding);
    tft.setTextDatum(TR_DATUM);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK, true);
    tft.drawString("B: ", x, y);

    tft.unloadFont();

    batteryTemperature = data.mainData.batteryTemperature;
}

void Main::drawGear()
{
    if (gear == data.mainData.gear)
        return;

    if (data.mainData.gear < 0)
        return;

    if (data.mainData.gear > 5)
        return;

    tft.loadFont(FONT_96);

    String gearString = String(data.mainData.gear);

    int textWidth = tft.textWidth("0");

    tft.setTextPadding(textWidth);

    int x = SCREEN_WIDTH / 2 - textWidth / 2;
    int y = SCREEN_HEIGHT / 2 + 28;

    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(COLOR_YELLOW, COLOR_BLACK, true);
    tft.drawString(gearString, x, y);

    tft.unloadFont();

    gear = data.mainData.gear;
}

void Main::drawEngineTemperature()
{
    if (engineTemperature == data.mainData.engineTemperature)
        return;

    int temperature = data.mainData.engineTemperature;

    if (temperature < -99)
        temperature = -99;

    tft.loadFont(FONT_28);

    String engineTemperatureString = String(temperature) + "°C";
    Color color = COLOR_GREEN;

    if (temperature < 0)
    {
        if (engineTemperatureString.length() > 5)
            return;
    }
    else
    {
        if (engineTemperatureString.length() > 5)
            return;
    }

    // Set color
    if (temperature < 0)
    {
        color = COLOR_BLUE;
    }
    else if (temperature < 25)
    {
        color = COLOR_CYAN;
    }
    else if (temperature < 70)
    {
        color = COLOR_GREEN;
    }
    else if (temperature < 90)
    {
        color = COLOR_YELLOW;
    }
    else
    {
        color = COLOR_RED;
    }

    int textWidth = tft.textWidth("000°C"); // Max length

    int x = 16;
    int y = SCREEN_HEIGHT - 8;

    int padding = tft.textWidth("B: ");
    tft.setTextPadding(padding);
    tft.setTextDatum(BL_DATUM);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK, true);
    tft.drawString("E: ", x, y);

    tft.setTextPadding(textWidth);
    tft.setTextDatum(BL_DATUM);
    tft.setTextColor(color, COLOR_BLACK, true);

    tft.drawString(engineTemperatureString, x + padding, y);

    tft.unloadFont();

    engineTemperature = data.mainData.engineTemperature;
}

void Main::drawControllerTemperature()
{
    if (controllerTemperature == data.mainData.controllerTemperature)
        return;

    int temperature = data.mainData.controllerTemperature;

    if (temperature < -99)
        temperature = -99;

    tft.loadFont(FONT_28);

    String controllerTemperatureString = String(temperature) + "°C";
    Color color = COLOR_GREEN;

    if (temperature < 0)
    {
        if (controllerTemperatureString.length() > 5)
            return;
    }
    else
    {
        if (controllerTemperatureString.length() > 5)
            return;
    }

    // Set color
    if (temperature < 0)
    {
        color = COLOR_BLUE;
    }
    else if (temperature < 25)
    {
        color = COLOR_CYAN;
    }
    else if (temperature < 70)
    {
        color = COLOR_GREEN;
    }
    else if (temperature < 90)
    {
        color = COLOR_YELLOW;
    }
    else
    {
        color = COLOR_RED;
    }

    int textWidth = tft.textWidth("000°C"); // Max length

    int x = SCREEN_WIDTH - 8 - textWidth;
    int y = SCREEN_HEIGHT - 8;

    tft.setTextPadding(textWidth);
    tft.setTextDatum(BL_DATUM);
    tft.setTextColor(color, COLOR_BLACK, true);

    tft.drawString(controllerTemperatureString, x, y);

    int padding = tft.textWidth("B: ");
    tft.setTextPadding(padding);
    tft.setTextDatum(BR_DATUM);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK, true);
    tft.drawString("C: ", x, y);

    tft.unloadFont();

    controllerTemperature = data.mainData.controllerTemperature;
}
