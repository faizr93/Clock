#include "alarm.h"
#include "button.h"
#include "globalConst.h"

Alarm::Alarm()
{
    isOn = false;
    color = DARKGRAY;

    rect.height = GetScreenWidth() / 7;
    rect.width = GetScreenWidth() - (10 * PADDING);
    rect.x = (GetScreenWidth() - rect.width) / 2;
    rect.y = (GetScreenHeight() - rect.height - PADDING) / 2;
    
    title.text = "0:00 AM";
    title.fontSize = rect.width / 7;
    title.y = rect.y + ((rect.height - title.fontSize) / 2) + 5;
    title.x = rect.x + (title.y - rect.y) + 5;
    
    initAlarmToggle();
}

void Alarm::toggle()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), alarmToggle.rect))
    {
        isOn = !isOn;
        alarmToggle.color = isOn ? DARKGREEN : RED;
        alarmToggle.title.text = (alarmToggle.title.text == "OFF" ? "ON" : "OFF");
    }
}

void Alarm::initAlarmToggle()
{
    initAlarmToggleTitle();
    initAlarmToggleRect();
    alarmToggle.color = RED;
}

void Alarm::initAlarmToggleRect()
{
    alarmToggle.rect.height = title.fontSize - 10;
    alarmToggle.rect.width = alarmToggle.rect.height + 10;
    alarmToggle.rect.x = rect.x + rect.width - (title.y - rect.y) - alarmToggle.rect.width;
    alarmToggle.rect.y = title.y;
}

void Alarm::initAlarmToggleTitle()
{
    alarmToggle.title.text = "OFF";
    alarmToggle.title.fontSize = alarmToggle.rect.width / 8;
    alarmToggle.title.x = rect.x + rect.width - (title.y - rect.y);
    alarmToggle.title.y = title.y;
}
