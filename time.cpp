#include <ctime>  // For time handling
#include "time.h" // For the declaration of getFormattedTime()
#include "text.h"

char *getFormattedTime()
{
    static char timeBuffer[100];
    time_t currentTime = std::time(nullptr);
    tm *time = std::localtime(&currentTime);
    std::strftime(timeBuffer, 100, "%r", time);
    return timeBuffer;
}

void setUpperText(DisplayedText &topLeftText, DisplayedText &topText, DisplayedText &topRightText)
{
    if (currentState == "TIME")
    {
        topLeftText.text = "Clock By Faiz";
        topText.text = "<WELCOME>";
        topRightText.text = "V1.0";
    }
    if (currentState == "STOPWATCH")
    {
        topLeftText.text = "Left->Toggle";
        topText.text = "<MouseClick>";
        topRightText.text = "Reset<-Right";
    }
    if (currentState == "ALARM")
    {
        topLeftText.text = "---";
        topText.text = "NOT IMPLEMENTED";
        topRightText.text = "---";
    }
}