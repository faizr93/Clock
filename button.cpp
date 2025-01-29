#include "button.h"
#include <raylib.h>
#include "globalConst.h"
#include <vector>

constexpr int TOTALNAVBUTTONS = 3;
constexpr int NAVBUTTONSPACING = 20; // of navbuttons buttons

Buttons buttons;

// Constructor, Initialize/Position To Default values
Button::Button()
{
    rect.height = GetScreenHeight() / 7;                                    // Keeps it Consistent Across Resizing
    rect.width = (GetScreenWidth() / TOTALNAVBUTTONS) - (NAVBUTTONSPACING); // All Equal Width, - magic number just for asthetic
    rect.x = PADDING;                                                       // Padding Applied at Left, Right, Bottom
    rect.y = GetScreenHeight() - rect.height - PADDING;                     // Perfect Positioning at the bottom
    color = RAYWHITE;                                                       // White Placeholder
    roundness = 0.69;
}

void Button::draw()
{
    DrawRectangleRounded(rect, roundness, 10, color);
    title.draw();
}

void Button::centerTitleRelative()
{
    int textWidth = MeasureText(title.text.c_str(), title.fontSize);
    // int centerPosX = (GetScreenWidth() - textWidth) / 2;
    title.x = rect.x + ((rect.width - textWidth) / 2);
    title.y = rect.y + ((rect.height - title.fontSize) / 2);
}

void initNavButtons(Button &defaultButton)
{
    /*
     * Calculates spacing between navigation buttons:
     * - Start with total screen width.
     * - Subtract left & right padding.
     * - Subtract total width of all buttons.
     * - Divide remaining space by gaps between buttons (TOTALNAVBUTTONS - 1).
     */

    float spacing = (GetScreenWidth() - (2 * PADDING) - (TOTALNAVBUTTONS * defaultButton.rect.width)) / (TOTALNAVBUTTONS - 1);
    for (size_t i = 0; i < TOTALNAVBUTTONS; i++)
    {
        buttons.push_back(defaultButton);
        buttons[i].title.text = states[i];
        buttons[i].rect.x = PADDING + i * (defaultButton.rect.width + spacing);
        buttons[i].title.fontSize = buttons[i].rect.width / 7;
        buttons[i].title.color = BLACK;
        buttons[i].centerTitleRelative();
    }
}

bool handleNavButtonClicks()
{
    // Check for mouse clicks
    if (!(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)))
        return false;

    Vector2 mousePos = GetMousePosition();
    const char *states[] = {"TIME", "STOPWATCH", "ALARM"};

    int i = 0;
    for (auto &button : buttons)
    {
        if (CheckCollisionPointRec(mousePos, button.rect))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                currentState = states[i];
            }
            return true;
        }
        i++;
    }
    return false;
}

void drawNavButtons()
{
    for (auto &button : buttons)
    {
        button.draw();
    }
}

void handleActiveButton()
{
    for (size_t i = 0; i < TOTALNAVBUTTONS; i++)
    {
        if (currentState == states[i])
        {
            // Iterates over All buttons and Sets All of them Except Active Button To Light Gray;
            for (size_t j = 0; j < TOTALNAVBUTTONS; j++)
            {
                buttons[j].color = (j == i) ? RED : LIGHTGRAY;
                buttons[j].title.color = (j == i) ? RAYWHITE : BLACK;
            }
            return;
        }
    }
}
