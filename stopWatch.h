#pragma once
#include <chrono>
#include <string>
#include "text.h"


struct Stopwatch
{
    bool started;
    bool firstRun;
    std::chrono::high_resolution_clock::time_point start;
    DisplayedText stopWatchText;

    Stopwatch();

    std::string getFormattedDuration(); // Function to get the formatted duration (MM:SS.CS)
    void handleInput();                 // Toggle, Reset
    void update();                      // When Its Running
    void draw();
};
