#pragma once
#include <string>
#include <raylib.h>
#include <vector>

// Forward
struct Button;
using Buttons = std::vector<Button>;
// Declaration
enum Position
{
    TOP,
    TOPLEFT,
    TOPRIGHT,
    CENTER_TEXT_RELATIVE,
    BUTTON_TEXT_RELATIVE,
    STATE_TEXT_RELATIVE
};

extern std::string currentState;
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
    void posText(Position position, Button &button);
    void initNavButtonText(Button &button);
    // void initButtonText(Rectangle parentRect)
};
