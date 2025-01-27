#pragma once

struct DisplayedText; // Forward Declaration

char *getFormattedTime(); // Gets the current system time and formats it as HH:MM:SS AM/PM., Returns CharArray with Formatted Time
void setUpperText(DisplayedText &topLeftText, DisplayedText &topText, DisplayedText &topRightText);