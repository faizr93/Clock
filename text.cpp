#include <raylib.h>
#include "text.h"
#include "button.h"
#include <iostream>
#include "globalConst.h"

const char *states[] = {"TIME", "STOPWATCH", "ALARM"};
std::string currentState = "ALARM";
Position pos;

DisplayedText::DisplayedText()
{
    topTextFontSize = 32;
    padding = PADDING;
    color = LIGHTGRAY;
    fontSize = GetScreenWidth() / 7; // Desired Width to Font Size Ratio
}
void DisplayedText::draw()
{
    DrawText(text.c_str(), x, y, fontSize, color);
}

void DisplayedText::posText(Position position, Button &button)
{
    int textWidth = MeasureText(text.c_str(), fontSize);
    int centerPos = (GetScreenWidth() - textWidth) / 2;

    switch (position)
    {
    case TOP:
        x = centerPos; // Centers it
        y = padding;
        break;
    case TOPLEFT:
        x = y = padding; // as the Origin is TopLeft
        break;
    case TOPRIGHT:
        x = GetScreenWidth() - textWidth - padding;
        y = padding;
        break;
    case STATE_TEXT_RELATIVE:
        x = centerPos;
        y = GetScreenHeight() / 6;
        break;
    case CENTER_TEXT_RELATIVE:
        x = centerPos;
        // y = (GetScreenHeight() - fontSize + stateText.fontSize) / 2;
        y = (GetScreenHeight() - fontSize - PADDING) / 2;
        break;
    case BUTTON_TEXT_RELATIVE:
        x = button.rect.x + ((button.rect.width - textWidth) / 2);
        y = button.rect.y + (button.rect.height - fontSize) / 2;
        break;
    default:
        break;
    }
}

void DisplayedText::initNavButtonText(Button &button)
{
    fontSize = button.rect.width / 7;
    color = BLACK;
    button.title.posText(BUTTON_TEXT_RELATIVE, button);
}