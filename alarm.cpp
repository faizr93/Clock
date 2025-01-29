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

    title.text = "6:00 Am";
    title.fontSize = rect.width / 7;
    title.y = rect.y + ((rect.height - title.fontSize) / 2) + 5;
    title.x = rect.x + (title.y - rect.y) + 5;
    
    initAlarmToggle();
}

void Alarm::toggle()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), alarmToggleButton.rect))
    {
        isOn = !isOn;
        alarmToggleButton.color = isOn ? DARKGREEN : RED;
        alarmToggleButton.title.text = (alarmToggleButton.title.text == "OFF" ? "ON" : "OFF");
    }
}

void Alarm::initAlarmToggle()
{
    alarmToggleButton.title.text = "OFF";
    alarmToggleButton.title.fontSize = alarmToggleButton.rect.width / 8;
    alarmToggleButton.title.x = rect.x + rect.width - (title.y - rect.y);
    alarmToggleButton.title.y = title.y;

    alarmToggleButton.rect.height = title.fontSize - 10;
    alarmToggleButton.rect.width = alarmToggleButton.rect.height + 10;
    alarmToggleButton.rect.x = rect.x + rect.width - (title.y - rect.y) - alarmToggleButton.rect.width;
    alarmToggleButton.rect.y = title.y;

    alarmToggleButton.color = RED;
}