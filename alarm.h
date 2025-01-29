#pragma once
#include "button.h"

struct Alarm : Button {  
    bool isOn;
    Button alarmToggleButton;

    Alarm();
    void toggle();
    void initAlarmToggle();
};