#include "torque.h"

using namespace TFT;

Torque::Torque()
{
}

void Torque::draw()
{
    // Clear variables
    torqueArray.fill(-1);
    gear = -1;
    engineTemperature = -1;
    controllerTemperature = -1;

    // Clear screen
    tft.clearScreen();

    // Draw dividers
    tft.drawDivider(SCREEN_HEIGHT - 41);
    tft.fillRect(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 40, COLOR_GRAY);

    // Draw chart
    drawChart();
    drawGear();
    drawEngineTemperature();
    drawControllerTemperature();
}

void Torque::update()
{
}

void Torque::drawChart()
{
    int chartWidth = 200;
    int chartHeight = 128;

    int padding = 8;

    int boxWidth = chartWidth + padding * 2;
    int boxHeight = chartHeight + padding * 2;
    int boxY = 28;
    int boxX = (SCREEN_WIDTH - boxWidth) / 2;

    tft.fillSmoothRoundRect(boxX, boxY, boxWidth, boxHeight, 4, COLOR_GRAY);
}

void Torque::drawGear()
{
    if (gear == data.torqueData.gear)
        return;

    if (data.torqueData.gear < 0)
        return;

    if (data.torqueData.gear > 5)
        return;

    tft.loadFont(FONT_96);

    String gearString = String(data.torqueData.gear);

    int textWidth = tft.textWidth("0");

    tft.setTextPadding(textWidth);

    int x = SCREEN_WIDTH / 2 - textWidth / 2;
    int y = SCREEN_HEIGHT / 2 + 32;

    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(COLOR_YELLOW, COLOR_BLACK, true);
    tft.drawString(gearString, x, y);

    tft.unloadFont();

    gear = data.torqueData.gear;
}

void Torque::drawEngineTemperature()
{
    if (engineTemperature == data.torqueData.engineTemperature)
        return;

    int temperature = data.torqueData.engineTemperature;

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
    tft.setTextColor(COLOR_WHITE, COLOR_GRAY, true);
    tft.drawString("E: ", x, y);

    tft.setTextPadding(textWidth);
    tft.setTextDatum(BL_DATUM);
    tft.setTextColor(color, COLOR_GRAY, true);

    tft.drawString(engineTemperatureString, x + padding, y);

    tft.unloadFont();

    engineTemperature = data.torqueData.engineTemperature;
}

void Torque::drawControllerTemperature()
{
    if (controllerTemperature == data.torqueData.controllerTemperature)
        return;

    int temperature = data.torqueData.controllerTemperature;

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
    tft.setTextColor(color, COLOR_GRAY, true);

    tft.drawString(controllerTemperatureString, x, y);

    int padding = tft.textWidth("B: ");
    tft.setTextPadding(padding);
    tft.setTextDatum(BR_DATUM);
    tft.setTextColor(COLOR_WHITE, COLOR_GRAY, true);
    tft.drawString("C: ", x, y);

    tft.unloadFont();

    controllerTemperature = data.torqueData.controllerTemperature;
}
