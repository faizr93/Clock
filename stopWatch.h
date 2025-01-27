#pragma once
#include <chrono>
#include <string>

struct DisplayedText;

// Returns String of Duration since Given Time Point, Formatted as MM:SS.Cs where Cs is centiseconds
std::string getFormattedDuration(std::chrono::high_resolution_clock::time_point start);

void toggleStopWatch(bool &isStopWatchStarted); // toggles The boolean