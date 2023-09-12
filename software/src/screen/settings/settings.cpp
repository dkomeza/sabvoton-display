#include "settings.h"

using namespace TFT;

void Settings::draw()
{
    tft.clearScreen();

    // Draw title
    tft.loadFont(FONT_28);
    tft.setTextDatum(TC_DATUM);
    tft.setTextColor(COLOR_WHITE, COLOR_BLACK, true);
    tft.setTextPadding(0);
    tft.drawString(title, SCREEN_WIDTH / 2, 16);
    tft.drawFastHLine(0, 56, SCREEN_WIDTH, COLOR_BACKGROUND_SECONDARY);
    tft.unloadFont();

    // Create categories
    int y = 86;
    int x = 16;
    int height = 32;
    int width = SCREEN_WIDTH - (x * 2);

    for (int i = 0; i < categoryNames.size(); i++)
    {
        BoundingBox boundingBox = {x, y, width, height};
        Category category = Category(categoryNames[i], boundingBox, i == hoveredOption);
        categories.push_back(category);

        y += 40;
    }

    drawCategories();
}

void Settings::drawCategories()
{
    // Clear settings
    tft.fillRect(0, 56, SCREEN_WIDTH, SCREEN_HEIGHT - 56, COLOR_BLACK);

    // Draw categories
    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].boundingBox.y - scrollOffset < 56)
        {
            continue;
        }

        if (categories[i].boundingBox.y - scrollOffset > SCREEN_HEIGHT - 32)
        {
            break;
        }

        categories[i].drawTitle();
    }
}

void Settings::hoverNextOption()
{
    if (hoveredOption < categories.size() - 1)
    {
        categories[hoveredOption].toggleHover();
        hoveredOption++;
        categories[hoveredOption].toggleHover();
    }
    else if (hoveredOption == categories.size() - 1)
    {
        categories[hoveredOption].toggleHover();
        hoveredOption = 0;
        categories[hoveredOption].toggleHover();
    }
}

void Settings::hoverPreviousOption()
{
    if (hoveredOption > 0)
    {
        categories[hoveredOption].toggleHover();
        hoveredOption--;
        categories[hoveredOption].toggleHover();
    }
    else if (hoveredOption == 0)
    {
        categories[hoveredOption].toggleHover();
        hoveredOption = categories.size() - 1;
        categories[hoveredOption].toggleHover();
    }
}

void Settings::selectOption(){

};

Category::Category(String title, TFT::BoundingBox boundingBox, bool selected)
{
    this->title = title;
    this->boundingBox = boundingBox;
    this->hover = selected;
}

void Category::drawTitle()
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

void Category::toggleHover()
{
    hover = !hover;
    drawTitle();
}
