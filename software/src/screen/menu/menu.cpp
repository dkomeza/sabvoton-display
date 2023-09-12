#include "menu.h"
#include "screen/screen.h"

using namespace TFT;

Menu::Menu()
{
}

void Menu::draw()
{
    // Clear screen
    tft.clearScreen();

    // Draw title
    String title = "Menu";
    tft.loadFont(FONT_28);
    tft.setTextDatum(TC_DATUM);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK, true);
    tft.setTextPadding(0);
    tft.drawString(title, SCREEN_WIDTH / 2, 16);
    tft.drawFastHLine(0, 56, SCREEN_WIDTH, COLOR_BACKGROUND_SECONDARY);
    tft.unloadFont();

    // Draw options
    for (int i = 0; i < 4; i++)
    {
        int y = 86 + (i * 40);
        int x = 16;
        int height = 32;
        int width = SCREEN_WIDTH - (x * 2);

        BoundingBox boundingBox = {x, y, width, height};
        MenuOption menuOption = MenuOption(options[i], boundingBox, i == hoveredOption);
        menuOptions[i] = menuOption;
    }

    // Draw power options
    int y = 86 + (4 * 40);
    int x = 16;
    int height = 32;
    int width = (SCREEN_WIDTH - (x * 2) - 8) / 2;

    BoundingBox boundingBox = {x, y, width, height};
    MenuOption menuOption = MenuOption(options[4], boundingBox, 4 == hoveredOption);
    menuOptions[4] = menuOption;

    x = x + width + 8;
    boundingBox = {x, y, width, height};
    menuOption = MenuOption(options[5], boundingBox, 5 == hoveredOption);
    menuOptions[5] = menuOption;

    assignActions();
}

void Menu::assignActions()
{
    menuOptions[0].onClick = []()
    {
        data.mode = MODE::MAIN;
        controller.changeMode(MODE::MAIN);
        Screen::changeView();
    };

    menuOptions[1].onClick = []()
    {
        data.mode = MODE::TORQUE;
        controller.changeMode(MODE::TORQUE);
        Screen::changeView();
    };

    menuOptions[2].onClick = []()
    {
        data.mode = MODE::SETTINGS;
        controller.changeMode(MODE::SETTINGS);
        Screen::changeView();
    };

    menuOptions[3].onClick = []()
    {
        data.mode = MODE::DATA;
        controller.changeMode(MODE::DATA);
        Screen::changeView();
    };
};

void Menu::selectOption()
{
    if (menuOptions[hoveredOption].onClick == NULL)
        return;

    menuOptions[hoveredOption].onClick();
}

void Menu::hoverNextOption()
{
    menuOptions[hoveredOption].toggleHover();

    hoveredOption = hoveredOption == 5 ? 0 : hoveredOption + 1;

    menuOptions[hoveredOption].toggleHover();
}

void Menu::hoverPreviousOption()
{
    menuOptions[hoveredOption].toggleHover();

    hoveredOption = hoveredOption == 0 ? 5 : hoveredOption - 1;

    menuOptions[hoveredOption].toggleHover();
}

MenuOption::MenuOption(String _title, BoundingBox _boundingBox, bool _selected)
{
    title = _title;
    boundingBox = _boundingBox;
    hover = _selected;

    draw();
}

void MenuOption::draw()
{
    tft.loadFont(FONT_18);

    uint32_t color = hover ? COLOR_BLACK : COLOR_WHITE;
    uint32_t backgroundColor = hover ? COLOR_SECONDARY : COLOR_BACKGROUND_SECONDARY;
    int padding = 10;

    tft.fillSmoothRoundRect(boundingBox.x, boundingBox.y, boundingBox.width, boundingBox.height, 4, backgroundColor, COLOR_BLACK);

    tft.setTextColor(color, backgroundColor, true);
    tft.setTextPadding(0);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(title, boundingBox.x + padding, boundingBox.y + (boundingBox.height / 2));

    tft.unloadFont();
}

void MenuOption::toggleHover()
{
    hover = !hover;
    draw();
}
