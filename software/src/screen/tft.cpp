#include "tft.h"

namespace TFT
{
    _TFT tft = _TFT(SCREEN_WIDTH, SCREEN_HEIGHT);
}

using namespace TFT;

void _TFT::clearScreen()
{
    this->fillScreen(this->backgroundColor);
}

void _TFT::clearScreen(Color color)
{
    this->fillScreen(color);
}

void _TFT::drawDivider(int y)
{
    this->drawLine(0, y, SCREEN_WIDTH, y, this->secondaryColor);
}

void _TFT::drawDivider(int y, Color color)
{
    this->drawLine(0, y, SCREEN_WIDTH, y, color);
}

void _TFT::drawButton(String text, int x, int y, int padding)
{
    this->drawButton(text, x, y, this->primaryColor, this->backgroundColor, padding);
}

void _TFT::drawButton(String text, TFT::BoundingBox boundingBox, int padding)
{
    this->drawButton(boundingBox, text, this->primaryColor, this->backgroundColor, padding);
}

void _TFT::drawButton(String text, int x, int y, Color color, Color backgroundColor, int padding)
{
    this->loadFont(FONT_18);

    int textWidth = this->textWidth(text);
    int textHeight = this->fontHeight();

    int width = textWidth + (padding * 2);
    int height = textHeight + (padding * 2);

    int textX = x + padding;
    int textY = y + padding;

    this->fillSmoothRoundRect(x, y, width, height, 8, backgroundColor);

    this->setTextColor(color, backgroundColor, true);
    this->drawString(text, textX, textY, 2);

    this->unloadFont();
}

void _TFT::drawButton(TFT::BoundingBox boundingBox, String text, Color color, Color backgroundColor, int padding)
{
    this->loadFont(FONT_18);

    int textWidth = this->textWidth(text);
    int textHeight = this->fontHeight();

    int width = textWidth + (padding * 2);
    int height = textHeight + (padding * 2);

    int textX = boundingBox.x + padding;
    int textY = boundingBox.y + padding;

    this->fillSmoothRoundRect(boundingBox.x, boundingBox.y, width, height, 8, backgroundColor);

    this->setTextColor(color, backgroundColor, true);
    this->drawString(text, textX, textY, 2);

    this->unloadFont();
}


