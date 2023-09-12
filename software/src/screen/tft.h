#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <vector>

// Load fonts
#include "fonts/Font18.h"
#include "fonts/Font28.h"
#include "fonts/Font96.h"
#include "fonts/Font164.h"

#define FONT_18 Baloo18
#define FONT_28 Inconsolata28
#define FONT_96 Inconsolata96
#define FONT_164 Inconsolata164

class _TFT;

namespace TFT
{
    // Screen constants
    static const int SCREEN_HEIGHT = 320;
    static const int SCREEN_WIDTH = 240;
    static const int TFT_BACKLIGHT_PIN = 26;

    // Color constants
    static const uint32_t COLOR_BLACK = TFT_BLACK;
    static const uint32_t COLOR_GRAY = 0x0821;
    static const uint32_t COLOR_WHITE = TFT_WHITE;
    static const uint32_t COLOR_RED = TFT_RED;
    static const uint32_t COLOR_GREEN = TFT_GREEN;
    static const uint32_t COLOR_BLUE = TFT_BLUE;
    static const uint32_t COLOR_YELLOW = TFT_YELLOW;
    static const uint32_t COLOR_CYAN = TFT_CYAN;
    static const uint32_t COLOR_BACKGROUND_SECONDARY = 0x2124;
    static const uint32_t COLOR_SECONDARY = 0xE71C;

    typedef uint32_t Color;

    extern _TFT tft;

    struct BoundingBox
    {
        int x;
        int y;
        int width;
        int height;
    };

    enum class TextAlign
    {
        LEFT,
        CENTER,
        RIGHT
    };

    enum class TextBaseline
    {
        TOP,
        MIDDLE,
        BOTTOM
    };

    enum class Position
    {
        RELATIVE,
        ABSOLUTE,
        FIXED
    };

    enum class Display
    {
        BLOCK,
        INLINE,
        FLEX
    };

    enum class FlexDirection
    {
        ROW,
        COLUMN
    };

    enum class JustifyContent
    {
        FLEX_START,
        FLEX_END,
        CENTER,
        SPACE_BETWEEN,
        SPACE_AROUND
    };

    enum class AlignItems
    {
        FLEX_START,
        FLEX_END,
        CENTER,
        BASELINE,
        STRETCH
    };

    enum class Font
    {
        FONT_18,
        FONT_28,
        FONT_96,
        FONT_164
    };

    struct Padding
    {
        int top;
        int right;
        int bottom;
        int left;
    };

    struct Margin
    {
        int top;
        int right;
        int bottom;
        int left;
    };

    struct Border
    {
        int width;
        Color color;
    };
}

class Element
{
public:
    Element();

    void render();
    void draw();

    // Element attributes
    bool selectable = false;
    bool hoverable = false;

    // Element content
    String text;
    TFT::TextAlign textAlign = TFT::TextAlign::LEFT;
    TFT::TextBaseline textBaseline = TFT::TextBaseline::TOP;
    TFT::Font font = TFT::Font::FONT_18;

    // Element relations
    Element *parent;
    std::vector<Element> children;
    TFT::Display display = TFT::Display::BLOCK;

    // Flexbox
    TFT::FlexDirection flexDirection = TFT::FlexDirection::ROW;
    TFT::JustifyContent justifyContent = TFT::JustifyContent::FLEX_START;
    TFT::AlignItems alignItems = TFT::AlignItems::FLEX_START;
    int columnGap = 0;
    int rowGap = 0;

    // Element position
    TFT::BoundingBox boundingBox;
    TFT::Position position = TFT::Position::RELATIVE;

    // Element style
    TFT::Color color;
    TFT::Color backgroundColor;
    TFT::Padding padding;
    TFT::Margin margin;
    TFT::Border border;
    int borderRadius = 0;
};

class _TFT : public TFT_eSPI
{
protected:
public:
    _TFT(int width, int height) : TFT_eSPI(width, height)
    {
        this->init();
    }

    TFT::Color primaryColor = TFT::COLOR_WHITE;
    TFT::Color secondaryColor = TFT::COLOR_SECONDARY;

    TFT::Color backgroundColor = TFT::COLOR_BLACK;
    TFT::Color backgroundSecondaryColor = TFT::COLOR_BACKGROUND_SECONDARY;

    void clearScreen();
    void clearScreen(TFT::Color color);

    void drawDivider(int y);
    void drawDivider(int y, TFT::Color color);

    void drawButton(String text, int x, int y, int padding = 10);
    void drawButton(String text, TFT::BoundingBox boundingBox, int padding = 10);
    void drawButton(String text, int x, int y, TFT::Color color, TFT::Color backgroundColor, int padding = 10);
    void drawButton(TFT::BoundingBox boundingBox, String text, TFT::Color color, TFT::Color backgroundColor, int padding = 10);
};
