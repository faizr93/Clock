#include <string>
#include <chrono>
#include <iomanip>
#include "stopWatch.h"
#include "text.h"

// Returns String of Duration since Given Time Point, Formatted as MM:SS.Cs where Cs is centiseconds
std::string getFormattedDuration(std::chrono::high_resolution_clock::time_point start)
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

void toggleStopWatch(bool &isStopWatchStarted)
{
    isStopWatchStarted = !isStopWatchStarted;
}