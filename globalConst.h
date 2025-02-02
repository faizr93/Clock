#pragma once
#include <string>
/*
 * This File is Not Expected To Make Sense On its Own, Its Code Context Matters
 * The Constants Here Are just To provide Meaning to Otherwise Magic Numbers
 * These Constants are Used Rarely and Hence are very specific and Easier to understand in Code Context.
 * Upon Looking at code and Changing some values You will automatically Come here to change something.
 */

constexpr int PADDING = 20;      // Primary Buttons at bottom, alarm, stopwatch, time
extern std::string currentState; // of text and navbuttons
extern const char *states[3];