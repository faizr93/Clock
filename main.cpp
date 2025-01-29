#include <raylib.h>
#include <iostream>
#include <chrono>
#include <vector>
#include "time.h"
#include "button.h"
#include "stopWatch.h"
#include "text.h"
#include "main.h"
#include "globalConst.h"
#include "alarm.h"

using namespace std;
using namespace chrono;

constexpr int UPPERTEXT_FONTSIZE = 32; // topleft, top and topright
constexpr int STATETEXT_FONTSIZE = 50;

int main()
{
    // Init Window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Clock");
    SetTargetFPS(75);

    // Init Buttons
    Button sampleButton;
    initNavButtons(sampleButton);

    DisplayedText topLeftText, topText, topRightText, timeText, stateText, alarmText; // Declare all Text
    timeText.text = getFormattedTime();                                               // Init Time Text
    stateText.text = currentState;                                                    // Init State Text

    setUpperText(topLeftText, topText, topRightText);

    // Init StopWatch
    Stopwatch stopwatch;

    // Init Text Colors
    topLeftText.color = topText.color = topRightText.color = GRAY;
    stateText.color = RED;

    // Init Font Sizes
    topLeftText.fontSize = topText.fontSize = topRightText.fontSize = UPPERTEXT_FONTSIZE;
    stateText.fontSize = STATETEXT_FONTSIZE;

    posText(topText, topLeftText, topRightText, stateText, timeText, buttons);

    Alarm alarm;
    bool alarmOn = false;
    while (!WindowShouldClose())
    {
        // Update

        if (handleNavButtonClicks())
        {
            stateText.text = currentState;
            setUpperText(topLeftText, topText, topRightText);
            posText(topText, topLeftText, topRightText, stateText, timeText, buttons);
            stopwatch.stopWatchText.posText(CENTER_TEXT_RELATIVE);
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        drawNavButtons();
        if (currentState == "TIME")
        {
            timeText.text = getFormattedTime();
            timeText.draw();
        }
        if (currentState == "STOPWATCH")
        {
            stopwatch.handleInput();
            stopwatch.update();
            stopwatch.draw();
        }
        if (currentState == "ALARM")
        {
            // Button alarmToggleButton;

            // Button hour, minuteTens, minuteOnes;
            // hour.rect.x = alarm.rect.x + alarm.rect.y + ((alarm.rect.height - alarm.title.fontSize) / 2) - alarm.rect.y;
            // hour.rect.y = alarm.rect.y + ((alarm.rect.height - alarm.title.fontSize) / 2);
            // hour.rect.height = alarmToggleButton.rect.width;
            // hour.rect.width = alarmToggleButton.rect.width - 20;
            //  = GetScreenWidth() / 7

            // DrawRectangleRounded(hour.rect, 0.4, 10, RED);

            alarm.toggle();
            alarm.alarmToggleButton.centerTitleRelative();

            DrawRectangleRounded(alarm.rect, 0.4, 10, DARKGRAY);
            DrawRectangleRounded(alarm.alarmToggleButton.rect, 0.4, 10, alarm.alarmToggleButton.color);
            alarm.title.draw();
            alarm.alarmToggleButton.title.draw();
        }
        handleActiveButton();
        drawUpperText(topLeftText, topText, topRightText);
        stateText.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void posText(DisplayedText &topText, DisplayedText &topLeftText, DisplayedText &topRightText, DisplayedText &stateText, DisplayedText &timeText, Buttons &buttons)
{
    // 1. Position independent elements first
    for (auto &button : buttons)
    {
        button.centerTitleRelative();
    }
    topText.posText(TOP);           // Top-centered
    topLeftText.posText(TOPLEFT);   // Top-left corner
    topRightText.posText(TOPRIGHT); // Top-right corner

    // 2. Position elements relative to the above
    timeText.posText(CENTER_TEXT_RELATIVE);

    // 3. Finally, position elements with the most dependencies
    stateText.posText(STATE_TEXT_RELATIVE);
}

void drawUpperText(DisplayedText &topLeftText, DisplayedText &topText, DisplayedText &topRightText)
{
    topLeftText.draw();
    topText.draw();
    topRightText.draw();
}