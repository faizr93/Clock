#pragma once
#include <raylib.h>
#include <vector>
#include "text.h"
/** BluePrint For Primary Navigation Buttons
- Time
- Alarm
- Stopwatch
 */
struct NavButton
{
    DisplayedText title; // Name that Appears on Hover or used instead of icon
    Rectangle rect;      // Visual Rectangle of the Button To be Displayed and Positioned
    Color color;
    float padding;

    /// @brief Creates & Positions Button Relative to Screen width/height at the bottom.
    NavButton(); // Constructor
};

using NavButtons = std::vector<NavButton>; // Alias for vector of Navigation Buttons

void initNavButtons(NavButtons &buttons, NavButton &defaultButton); // Adds 3 Buttons(auto positioned properties) To Given std::vector<NavButton>
void drawNavButtons(NavButtons &buttons);                           // Renders the Buttons from std::vector<NavButton>
bool handleNavButtonClicks(NavButtons &buttons);                              // Time, Alarm and Stopwatch Screen Navigation / Primary nav