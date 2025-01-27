#include <raylib.h>
#include <iostream>
#include <chrono>
#include <vector>
#include "time.h"
#include "navButton.h"
#include "stopWatch.h"
#include "text.h"
#include "main.h"
#define UPPERTEXT_FONTSIZE 32
#define STATETEXT_FONTSIZE 50
using namespace std;
using namespace chrono;

int main()
{
    // Init Window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Clock");
    SetTargetFPS(75);

    // Init Buttons
    vector<NavButton> buttons;
    NavButton sampleButton;
    initNavButtons(buttons, sampleButton);

    DisplayedText topLeftText, topText, topRightText, timeText, stopWatchText, stateText; // Declare all Text
    timeText.text = getFormattedTime();                                                   // Init Time Text
    stateText.text = currentState;                                                        // Init State Text
    setUpperText(topLeftText, topText, topRightText);

    // Init StopWatch
    auto start = std::chrono::high_resolution_clock::now();
    stopWatchText.text = getFormattedDuration(start).c_str();
    bool stopWatchStarted = 0;
    bool firstRunStopWatch = 1;

    // Init Text Colors
    topLeftText.color = topText.color = topRightText.color = stateText.color = RED;

    // Init Font Sizes
    topLeftText.fontSize = topText.fontSize = topRightText.fontSize = UPPERTEXT_FONTSIZE;
    stateText.fontSize = STATETEXT_FONTSIZE;

    // Positition All Text
    posText(timeText, topText, sampleButton, stopWatchText, topLeftText, topRightText, stateText);
    for (auto &button : buttons)
    {
        button.title.initNavButtonText(button, topText, timeText);
    }
    while (!WindowShouldClose())
    {
        // Update
        handleNavButtonClicks(buttons);
        stateText.text = currentState;

        // posText(timeText, topText, sampleButton, stopWatchText, topLeftText, topRightText, stateText); // except Button Text
        if (handleNavButtonClicks(buttons))
        {
            stateText.text = currentState;
            setUpperText(topLeftText, topText, topRightText);
            posText(timeText, topText, sampleButton, stopWatchText, topLeftText, topRightText, stateText);
        }
        for (auto &button : buttons)
        {
            button.title.initNavButtonText(button, topText, timeText);
        }
        // Render
        BeginDrawing();
        ClearBackground(BLACK);

        drawNavButtons(buttons);
        if (currentState == "TIME")
        {
            buttons[0].color = RED;
            buttons[1].color = RAYWHITE;
            buttons[2].color = RAYWHITE;

            timeText.text = getFormattedTime();
            timeText.draw();
        }
        if (currentState == "STOPWATCH")
        {
            buttons[0].color = RAYWHITE;
            buttons[1].color = RED;
            buttons[2].color = RAYWHITE;

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
        drawUpperText(topLeftText, topText, topRightText);
        stateText.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void posText(DisplayedText &timeText, DisplayedText &topText, NavButton &sampleButton, DisplayedText &stopWatchText, DisplayedText &topLeftText, DisplayedText &topRightText, DisplayedText &stateText, NavButtons buttons)
{
    {
        // Order matters! Start with independent elements.

        // 1. Position independent elements first
        topText.posText(TOP, topText, timeText, sampleButton);           // Top-centered, no dependencies
        topLeftText.posText(TOPLEFT, topText, timeText, sampleButton);   // Top-left corner
        topRightText.posText(TOPRIGHT, topText, timeText, sampleButton); // Top-right corner

        // 2. Position elements relative to the above
        timeText.posText(CENTER_TEXT_RELATIVE, topText, timeText, sampleButton);      // Relative to topText
        stopWatchText.posText(CENTER_TEXT_RELATIVE, topText, timeText, sampleButton); // Same as timeText

        // 3. Finally, position elements with the most dependencies
        stateText.posText(STATE_TEXT_RELATIVE, topText, timeText, sampleButton); // Relies on both topText and timeText
        for (auto &button : buttons)
        {
            button.title.posText(BUTTON_TEXT_RELATIVE, topText, timeText, button);
        }
    }
}

void drawUpperText(DisplayedText &topLeftText, DisplayedText &topText, DisplayedText &topRightText)
{
    topLeftText.draw();
    topText.draw();
    topRightText.draw();
}
