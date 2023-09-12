#include "screen.h"
#include "tft.h"

using namespace TFT;

namespace Screen
{
    Menu menu;
    Main view_main;
    Torque torque;
    Settings settings;

    void setup()
    {
        TFT::tft.init();
        TFT::tft.setRotation(4);

        pinMode(TFT::TFT_BACKLIGHT_PIN, OUTPUT);
        digitalWrite(TFT::TFT_BACKLIGHT_PIN, HIGH);

        TFT::tft.fillScreen(TFT_BLACK);

        changeView();
    }

    void changeView()
    {
        switch (data.mode)
        {
        case MODE::MENU:
            menu.draw();
            break;

        case MODE::MAIN:
            view_main.draw();
            break;
        case MODE::TORQUE:
            torque.draw();
            break;
        case MODE::SETTINGS:
            settings.draw();
            break;
        }
    }

    void drawPacket(byte buffer[], int size)
    {
        tft.clearScreen();

        for (int i = 0; i < size; i++)
        {
            tft.loadFont(FONT_28);
            tft.setTextDatum(TC_DATUM);
            tft.setTextColor(COLOR_WHITE, COLOR_BLACK, true);
            tft.setTextPadding(0);
            tft.drawString(String(buffer[i]), SCREEN_WIDTH / 2, 16 + (i * 32));
            tft.unloadFont();
        }
    }
}