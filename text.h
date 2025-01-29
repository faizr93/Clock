#pragma once
#include <string>
#include <raylib.h>

// Forward
struct Button;
// Declaration
enum Position
{
    TOP,
    TOPLEFT,
    TOPRIGHT,
    CENTER_TEXT_RELATIVE,
    STATE_TEXT_RELATIVE
};

extern Position pos;
struct DisplayedText
{
    std::string text;
    Color color;
    int x;
    int y;
    int fontSize;
    int topTextFontSize; // Needed for Relative Spacing, its a Workaround
    int padding;
    DisplayedText();
    void draw();
    void posText(Position position);
};
