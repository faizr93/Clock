#include "navButton.h"
#include <raylib.h>
#include "globalConst.h"

// Constructor, Initialize/Position To Default values
NavButton::NavButton()
{
    padding = PADDING;
    rect.height = GetScreenHeight() / 7;                                                  // Keeps it Consistent Across Resizing
    rect.width = (GetScreenWidth() / TOTALNAVBUTTONS) - (OUTLINETHICKNESS)-10;            // All Equal Width, - 30 just for asthetic
    rect = {padding, GetScreenHeight() - rect.height - padding, rect.width, rect.height}; // Perfect Positioning at the bottom
    color = RAYWHITE;                                                                     // White Placeholder
}

void initNavButtons(NavButtons &buttons, NavButton &defaultButton)
{
    const char *states[] = {"Time", "Stopwatch", "Alarm"};
    float spacing = (GetScreenWidth() - (2 * defaultButton.padding) - (TOTALNAVBUTTONS * defaultButton.rect.width)) / (TOTALNAVBUTTONS - 1);

    for (size_t i = 0; i < TOTALNAVBUTTONS; i++)
    {
        buttons.push_back(defaultButton);
        buttons[i].title.text = states[i];
        buttons[i].rect.x = defaultButton.padding + i * (defaultButton.rect.width + spacing);
    }
}

bool handleNavButtonClicks(NavButtons &buttons)
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

void drawNavButtons(NavButtons &buttons)
{
    for (auto &button : buttons)
    {
        // DrawRectangleRec(button.rect, button.color);
        DrawRectangleRounded(button.rect, 0.69, 1000, button.color);
        // DrawRectangleLinesEx(button.rect, 5, BLACK);
        // DrawRectangleLines(button.rect.x,button.rect.y,button.rect.width,button.rect.height,BLACK);
        DrawRectangleRoundedLines(button.rect, 0.69, 1000, OUTLINETHICKNESS, BLACK);
        // button.title.initNavButtonText();
        button.title.draw();
    }
}

