#pragma once
#include "button.h"

struct Alarm : Button {  
    bool isOn;
    Button alarmToggle;

    Button hour;
    Button minuteOnes;
    Button minuteTens;

    Alarm();

    void inithour();
    void initminuteOnes();
    void initminuteTens();
    void toggle();
    void initAlarmToggle();
    void initAlarmToggleRect();
    void initAlarmToggleTitle();
};


