#pragma once
#include <raylib.h>
#include <vector>
#include "text.h"

/** BluePrint For Primary Navigation Buttons
- Time
- Alarm
- Stopwatch
 */
struct Button
{
    DisplayedText title; // Name that Appears on Hover or used instead of icon
    Rectangle rect;      // Visual Rectangle of the Button To be Displayed and Positioned
    Color color;
    float roundness;

    /// @brief Creates & Positions Button Relative to Screen width/height at the bottom.
    Button(); // Constructor
    void draw();
    void centerTitleRelative();
};

using Buttons = std::vector<Button>; // Alias for vector of Navigation Buttons
extern Buttons buttons;

void initNavButtons(Button &defaultButton); // Adds 3 Buttons(auto positioned properties) To Given std::vector<Button>
void drawNavButtons();                        // Renders the Buttons from std::vector<Button>
bool handleNavButtonClicks();                 // Time, Alarm and Stopwatch Screen Navigation / Primary nav