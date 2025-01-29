#include <string>
#include <chrono>
#include <iomanip>
#include "stopWatch.h"
#include "text.h"
#include "button.h"

Stopwatch::Stopwatch()
{
    started = false;
    firstRun = true;
    stopWatchText.text = "00:00.00";
    stopWatchText.posText(CENTER_TEXT_RELATIVE);
    start = std::chrono::high_resolution_clock::now();
}

// Function to get the formatted duration (MM:SS.CS)
std::string Stopwatch::getFormattedDuration()
{
    auto end = std::chrono::high_resolution_clock::now();
    auto diff = end - start;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(diff);                                                 // Convert to minutes
    auto remainingSeconds = std::chrono::duration_cast<std::chrono::seconds>(diff - minutes);                              // Get remaining seconds (after full minutes)
    auto remainingMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff - minutes - remainingSeconds); // Get remaining milliseconds for centiseconds
    int centiseconds = remainingMilliseconds.count() / 10;                                                                 // Convert milliseconds to centiseconds 100ms = 10 centiseconds

    // Format as MM:SS.centiseconds
    std::ostringstream mystring;
    mystring << std::setfill('0') << std::setw(2) << minutes.count() << ":"
             << std::setw(2) << remainingSeconds.count() % 60 << "."
             << std::setw(2) << centiseconds;

    return mystring.str();
}

void Stopwatch::handleInput()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !handleNavButtonClicks())
    {
        firstRun = false;
        started = !started;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !started && !handleNavButtonClicks())
    {
        firstRun = true;
        start = std::chrono::high_resolution_clock::now();
        stopWatchText.text = "00:00.00";
    }
}

void Stopwatch::update()
{
    if (firstRun)
    {
        start = std::chrono::high_resolution_clock::now();
    }
    if (started)
    {
        stopWatchText.text = getFormattedDuration(); // Use the internal function to get the formatted time
    }
}

void Stopwatch::draw()
{
    stopWatchText.draw();
}
