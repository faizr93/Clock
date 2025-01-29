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
    timeText.text = getFormattedTime();                                                              // Init Time Text
    stateText.text = currentState;                                                                   // Init State Text

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
        // handleNavButtonClicks(); // This Function is Both a bool and A self contained function.
        if (handleNavButtonClicks())
        {
            stateText.text = currentState;
            setUpperText(topLeftText, topText, topRightText);
            posText(topText, topLeftText, topRightText, stateText, timeText, buttons);
        }

        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        drawNavButtons();
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

            stopwatch.handleInput();
            stopwatch.update();
            stopwatch.stopWatchText.posText(CENTER_TEXT_RELATIVE);
            stopwatch.draw();
        }
        if (currentState == "ALARM")
        {
            buttons[0].color = LIGHTGRAY;
            buttons[1].color = LIGHTGRAY;
            buttons[2].color = RED;
            buttons[0].title.color = BLACK;
            buttons[1].title.color = BLACK;
            buttons[2].title.color = RAYWHITE;

            

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
            hour.rect.x = alarm.rect.x + alarm.rect.y + ((alarm.rect.height - alarm.title.fontSize) / 2) - alarm.rect.y;
            hour.rect.y = alarm.rect.y + ((alarm.rect.height - alarm.title.fontSize) / 2);
            hour.rect.height = alarmToggle.rect.width;
            hour.rect.width = alarmToggle.rect.width - 20;
            //  = GetScreenWidth() / 7

            DrawRectangleRounded(alarm.rect, 0.4, 10, DARKGRAY);
            DrawRectangleRounded(hour.rect, 0.4, 10, RED);
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
            alarmToggle.centerTitleRelative();
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