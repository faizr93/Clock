#include <raylib.h>
#include "text.h"
#include "button.h"
#include <iostream>
#include "globalConst.h"

Position pos;

DisplayedText::DisplayedText()
{
    topTextFontSize = 32;
    color = LIGHTGRAY;
    fontSize = GetScreenWidth() / 7; // Desired Width to Font Size Ratio
}
void DisplayedText::draw()
{
    DrawText(text.c_str(), x, y, fontSize, color);
}

void DisplayedText::posText(Position position)
{
    int textWidth = MeasureText(text.c_str(), fontSize);
    int centerPosX = (GetScreenWidth() - textWidth) / 2;
    switch (position)
    {
    case TOP:
        x = centerPosX; // Centers it
        y = PADDING;
        break;
    case TOPLEFT:
        x = y = PADDING; // as the Origin is TopLeft
        break;
    case TOPRIGHT:
        x = GetScreenWidth() - textWidth - PADDING;
        y = PADDING;
        break;
    case STATE_TEXT_RELATIVE:
        x = centerPosX;
        y = GetScreenHeight() / 6;
        break;
    case CENTER_TEXT_RELATIVE:
        x = centerPosX;
        y = (GetScreenHeight() - fontSize - PADDING) / 2;
        break;
    default:
        break;
    }
}