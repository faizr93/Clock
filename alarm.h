#pragma once
#include "button.h"

struct Alarm : Button {  
    bool isOn;
    Button toggleAlarm;

    Alarm();
    void toggle();
};