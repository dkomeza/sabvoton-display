#pragma once

#include <vector>

#include "screen/tft.h"

typedef void (*Action)(void);

class Setting
{
public:
    Setting() {}
    
};

class Category
{
public:
    Category(){};
    Category(String title, TFT::BoundingBox boundingBox, bool selected);

    void drawTitle();
    void toggleHover();

    // Actions
    Action onClick = NULL;

    TFT::BoundingBox boundingBox;

private:
    String title;
    bool hover;
};

class Settings
{
public:
    void draw();

    void hoverNextOption();
    void hoverPreviousOption();

    void selectOption();

private:
    String title = "Settings";
    std::vector<String> categoryNames = {"General", "Torque", "Throttle"};

    std::vector<Category> categories;

    int hoveredOption = 0; // 0 - ?
    int scrollOffset = 0;
    bool selectedCategory = false;

    void drawCategories();
};