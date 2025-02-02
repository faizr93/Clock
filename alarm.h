#pragma once
#include "button.h"

struct Alarm : Button
{
    bool isOn;
    bool isRinging;
    Button alarmToggle;

    Button hour;
    Button minuteOnes;
    Button minuteTens;
    Button AMPM;
    Music alarmRingtone;

    DisplayedText semiColon;

    Alarm();

    std::vector<Button *> initTimeButtons();

    void updateTimeButtonRects();

    void handleInput();
    void positionTimeElements();
    void drawTimeElements();
    void initAlarmToggle();
    void draw();

    int getAlarmTimeInMinutes(const std::string &time_string);
    int getCurrentTimeInMinutes();

    void handleRing();

};
