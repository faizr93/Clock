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
    vector<Button> buttons;
    Button sampleButton;
    initNavButtons(buttons, sampleButton);

    DisplayedText topLeftText, topText, topRightText, timeText, stopWatchText, stateText, alarmText; // Declare all Text
    timeText.text = getFormattedTime();                                                              // Init Time Text
    stateText.text = currentState;                                                                   // Init State Text

    setUpperText(topLeftText, topText, topRightText);

    // Init StopWatch
    auto start = std::chrono::high_resolution_clock::now();
    stopWatchText.text = getFormattedDuration(start).c_str();
    bool stopWatchStarted = 0;
    bool firstRunStopWatch = 1;

    // Init Text Colors
    topLeftText.color = topText.color = topRightText.color = GRAY;
    stateText.color = RED;

    // Init Font Sizes
    topLeftText.fontSize = topText.fontSize = topRightText.fontSize = UPPERTEXT_FONTSIZE;
    stateText.fontSize = STATETEXT_FONTSIZE;

    // Positition All Text
    for (auto &button : buttons)
    {
        button.title.initNavButtonText(button);
    }
    posText(timeText, topText, sampleButton, stopWatchText, topLeftText, topRightText, stateText, buttons);

    bool alarmOn = false;
    while (!WindowShouldClose())
    {
        // Update
        handleNavButtonClicks(buttons); // This Function is Both a bool and A self contained function.
        if (handleNavButtonClicks(buttons))
        {
            stateText.text = currentState;
            setUpperText(topLeftText, topText, topRightText);
            posText(timeText, topText, sampleButton, stopWatchText, topLeftText, topRightText, stateText, buttons);
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        drawNavButtons(buttons);
        if (currentState == "TIME")
        {
            buttons[0].color = RED;
            buttons[1].color = LIGHTGRAY;
            buttons[2].color = LIGHTGRAY;
            buttons[0].title.color = RAYWHITE;
            buttons[1].title.color = BLACK;
            buttons[2].title.color = BLACK;

            timeText.text = getFormattedTime();
            timeText.draw();
        }
        if (currentState == "STOPWATCH")
        {
            buttons[0].color = LIGHTGRAY;
            buttons[1].color = RED;
            buttons[2].color = LIGHTGRAY;
            buttons[0].title.color = BLACK;
            buttons[1].title.color = RAYWHITE;
            buttons[2].title.color = BLACK;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !handleNavButtonClicks(buttons))
            {
                firstRunStopWatch = 0;             // As Soon as its Clicked, This Flag is Set to 0 Until Reset
                toggleStopWatch(stopWatchStarted); // Left button: Toggle Start/Stop
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !handleNavButtonClicks(buttons) && !stopWatchStarted) // Right button: Reset stopwatch On Stopped State
            {
                firstRunStopWatch = 1;
                start = std::chrono::high_resolution_clock::now(); // Reset start time
                stopWatchText.text = "00:00.00";                   // Reset the display text
            }
            if (firstRunStopWatch)
            {
                start = std::chrono::high_resolution_clock::now();
            }
            if (stopWatchStarted) // If stopwatch is running
            {
                stopWatchText.text = getFormattedDuration(start).c_str(); // Display the elapsed time
            }
            stopWatchText.draw();
        }
        if (currentState == "ALARM")
        {
            buttons[0].color = LIGHTGRAY;
            buttons[1].color = LIGHTGRAY;
            buttons[2].color = RED;
            buttons[0].title.color = BLACK;
            buttons[1].title.color = BLACK;
            buttons[2].title.color = RAYWHITE;

            Button alarm;
            int height = GetScreenWidth() / 7;
            alarm.rect.height = height;
            alarm.rect.width = GetScreenWidth() - (10 * PADDING);
            alarm.rect.y = (GetScreenHeight() - height - PADDING) / 2;
            alarm.rect.x = (GetScreenWidth() - alarm.rect.width) / 2;
            alarm.title.text = "6:00 Am";
            alarm.title.fontSize = alarm.rect.width / 7;
            alarm.title.y = alarm.rect.y + ((alarm.rect.height - alarm.title.fontSize) / 2) + 5;
            alarm.title.x = alarm.rect.x + (alarm.title.y - alarm.rect.y) + 5;

            Button alarmToggle;
            alarmToggle.title.text = "ON";
            alarmToggle.title.fontSize = alarmToggle.rect.width / 8;
            alarmToggle.title.x = alarm.rect.x + alarm.rect.width - (alarm.title.y - alarm.rect.y);
            alarmToggle.title.y = alarm.title.y;

            alarmToggle.rect.height = alarm.title.fontSize - 10;
            alarmToggle.rect.width = alarmToggle.rect.height + 10;
            alarmToggle.rect.x = alarm.rect.x + alarm.rect.width - (alarm.title.y - alarm.rect.y) - alarmToggle.rect.width;
            alarmToggle.rect.y = alarm.title.y;
            
            Button hour, minuteTens, minuteOnes;
            hour.rect.x = alarm.rect.x + ((alarm.rect.y + ((alarm.rect.height - alarm.title.fontSize) / 2) + 5) - alarm.rect.y) + 5;
            hour.rect.y = alarm.rect.y + ((alarm.rect.height - alarm.title.fontSize) / 2) + 5;
            hour.rect.height = alarmToggle.rect.width / 7;
            hour.rect.width = alarmToggle.rect.width - 10;
            //  = GetScreenWidth() / 7

            DrawRectangleRounded(hour.rect, 0.4, 10, DARKGRAY);
            DrawRectangleRounded(alarm.rect, 0.4, 10, DARKGRAY);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), alarmToggle.rect))
            {
                alarmOn = !alarmOn;
            }
            if (alarmOn)
            {
                alarmToggle.color = DARKGREEN;
                alarmToggle.title.text = "ON";
            }
            if (!alarmOn)
            {
                alarmToggle.color = RED;
                alarmToggle.title.text = "OFF";
            }
            alarmToggle.title.posText(BUTTON_TEXT_RELATIVE, alarmToggle);
            DrawRectangleRounded(alarmToggle.rect, 0.4, 10, alarmToggle.color);
            alarm.title.draw();
            alarmToggle.title.draw();
        }

        drawUpperText(topLeftText, topText, topRightText);
        stateText.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void posText(DisplayedText &timeText, DisplayedText &topText, Button &sampleButton, DisplayedText &stopWatchText, DisplayedText &topLeftText, DisplayedText &topRightText, DisplayedText &stateText, Buttons buttons)
{
    {
        // 1. Position independent elements first
        for (auto &button : buttons)
        {
            button.title.posText(BUTTON_TEXT_RELATIVE, button);
        }
        topText.posText(TOP, sampleButton);           // Top-centered
        topLeftText.posText(TOPLEFT, sampleButton);   // Top-left corner
        topRightText.posText(TOPRIGHT, sampleButton); // Top-right corner

        // 2. Position elements relative to the above
        timeText.posText(CENTER_TEXT_RELATIVE, sampleButton);
        stopWatchText.posText(CENTER_TEXT_RELATIVE, sampleButton);

        // 3. Finally, position elements with the most dependencies
        stateText.posText(STATE_TEXT_RELATIVE, sampleButton);
    }
}

void drawUpperText(DisplayedText &topLeftText, DisplayedText &topText, DisplayedText &topRightText)
{
    topLeftText.draw();
    topText.draw();
    topRightText.draw();
}