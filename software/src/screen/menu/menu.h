#pragma once

#include <Arduino.h>
#include <vector>

class Menu;

#include "data/data.h"
#include "screen/tft.h"
#include "controller/controller.h"

typedef void (*Action)(void);

class MenuOption
{
public:
    MenuOption(){};
    MenuOption(String title, TFT::BoundingBox boundingBox, bool selected);

    void draw();
    void toggleHover();

    // Actions
    Action onClick = NULL;

private:
    String title;
    TFT::BoundingBox boundingBox;
    bool hover;
};

class Menu
{
public:
    Menu();

    void draw();

    void hoverNextOption();
    void hoverPreviousOption();

    void selectOption();

private:
    String options[6] = {"Main", "Torque", "Settings", "Data", "Power On", "Power Off"};
    String title = "Menu";

    int hoveredOption = 0; // 0 - 5

    MenuOption menuOptions[6];

    void assignActions();
};