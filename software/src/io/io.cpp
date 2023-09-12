#include "io.h"

using namespace IO_Private;

void IO::setup()
{
    buttonDown.onClick(buttonDownOnClick);
    buttonPower.onClick(buttonPowerOnClick);
    buttonPower.onDoubleClick(buttonPowerOnDoubleClick);
    buttonUp.onClick(buttonUpOnClick);

    lastUpdate = millis();
}

void IO::update()
{
    // Prevent rollower
    if (millis() < lastUpdate)
        lastUpdate = millis();

    // Control update interval
    if (millis() - lastUpdate < updateInterval)
        return;

    buttonDown.update();
    buttonPower.update();
    buttonUp.update();

    lastUpdate = millis();
}

void IO_Private::buttonUpOnClick()
{
    switch (data.mode)
    {
    case MODE::MENU:
        Screen::menu.hoverPreviousOption();
        break;
    case MODE::MAIN:
        controller.increaseGear();
        break;
    case MODE::SETTINGS:
        Screen::settings.hoverPreviousOption();
        break;
    }
}

void IO_Private::buttonPowerOnClick()
{
    switch (data.mode)
    {
    case MODE::MENU:
        Screen::menu.selectOption();
        break;
    case MODE::SETTINGS:
        Screen::settings.selectOption();
        break;

    default:
        break;
    }
}

void IO_Private::buttonPowerOnDoubleClick()
{
    if (data.mode != MODE::MENU)
    {
        data.mode = MODE::MENU;
        Screen::changeView();
        controller.changeMode(MODE::MENU);
    }
}

void IO_Private::buttonDownOnClick()
{
    switch (data.mode)
    {
    case MODE::MENU:
        Screen::menu.hoverNextOption();
        break;
    case MODE::MAIN:
        controller.decreaseGear();
        break;
    case MODE::SETTINGS:
        Screen::settings.hoverNextOption();
        break;

    default:
        break;
    }
}