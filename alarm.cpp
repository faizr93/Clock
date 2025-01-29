#include "alarm.h"
#include "button.h"
#include "globalConst.h"

Alarm::Alarm()
{
    isOn = false;
    title.text = "6:00 AM";
    color = DARKGRAY;

    rect.height = GetScreenWidth() / 7;
    rect.width = GetScreenWidth() - (10 * PADDING);
    rect.x = (GetScreenWidth() - rect.width) / 2;
    rect.y = (GetScreenHeight() - rect.height - PADDING) / 2;
}

void Alarm::toggle()
{
    isOn = !isOn;
    color = isOn ? DARKGREEN : RED;
}
