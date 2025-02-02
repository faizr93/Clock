#include "alarm.h"
#include "button.h"
#include "globalConst.h"
#include <iostream>
#include <chrono>
#include <sstream>
Alarm::Alarm()
{
    isOn = false;
    color = GRAY;

    rect.height = GetScreenWidth() / 7;
    rect.width = GetScreenWidth() - (10 * PADDING);
    rect.x = (GetScreenWidth() - rect.width) / 2;
    rect.y = (GetScreenHeight() - rect.height - PADDING) / 2;

    title.text = ""; // Title itself is not Drawn, its used as Reference For Other Elements
    title.fontSize = rect.width / 7;
    title.y = rect.y + ((rect.height - title.fontSize) / 2) + 5;
    title.x = rect.x + (title.y - rect.y) + 5;
    padding = 15;
    alarmRingtone = LoadMusicStream("alarmRingtone.wav");
}

std::vector<Button *> Alarm::initTimeButtons()
{
    // Create a default template for time buttons.
    Button timeButton;
    timeButton.title.fontSize = title.fontSize;
    timeButton.title.color = title.color;
    timeButton.rect.height = title.fontSize;
    timeButton.color = DARKGRAY;
    timeButton.padding = 20;
    timeButton.roundness = 0.3;

    // Set default texts for hour, minute tens, minute ones, AM/PM, and Toggle.
    std::vector<std::string> timeParts = {"12", "0", "0", "AM", "OFF"};
    // Note: alarmToggle is included as the last element.
    std::vector<Button *> timeButtons = {&hour, &minuteTens, &minuteOnes, &AMPM, &alarmToggle};

    // Apply template and assign texts.
    for (size_t i = 0; i < timeButtons.size(); i++)
    {
        *timeButtons[i] = timeButton;
        timeButtons[i]->title.text = timeParts[i];
    }

    // Initialize the alarm toggle (its title and rect).
    initAlarmToggle();

    // Initialize the semicolon element.
    semiColon.text = ":";
    semiColon.fontSize = title.fontSize;
    semiColon.color = title.color;

    AMPM.title.fontSize = 50;

    return timeButtons;
}

void Alarm::updateTimeButtonRects()
{
    // Calculate position offsets and widths for each button
    float padding = 15;
    float xOffset = rect.x + padding;

    // Update rect properties for each time button
    std::vector<Button *> timeButtons = {&hour, &minuteTens, &minuteOnes, &AMPM};
    for (size_t i = 0; i < timeButtons.size(); i++)
    {
        // Update the rect width based on text and padding
        timeButtons[i]->rect.width = static_cast<float>(
                                         MeasureText(timeButtons[i]->title.text.c_str(), timeButtons[i]->title.fontSize)) +
                                     timeButtons[i]->padding;

        // Position button horizontally
        timeButtons[i]->rect.x = xOffset;
        timeButtons[i]->rect.y = rect.y + (rect.height - timeButtons[i]->rect.height) / 2;

        // Center the title
        timeButtons[i]->centerTitleRelative();
        timeButtons[i]->title.y = title.y;

        // Move to the next button's position
        xOffset += timeButtons[i]->rect.width + padding;
    }

    // Update the semicolon position between hour and minuteTens
    semiColon.x = ((hour.rect.x + hour.rect.width) + minuteTens.rect.x -
                   MeasureText(semiColon.text.c_str(), semiColon.fontSize)) /
                  2;
    semiColon.y = title.y;

    minuteOnes.rect.x = minuteTens.rect.x + minuteTens.rect.width - 10;
    AMPM.rect.x = minuteOnes.rect.x + minuteOnes.rect.width + padding;

    alarmToggle.centerTitleRelative();
    minuteOnes.centerTitleRelative();
    minuteOnes.title.y = title.y;
    AMPM.centerTitleRelative();
}
void Alarm::handleInput()
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;

    Vector2 mousePos = GetMousePosition();

    if (CheckCollisionPointRec(mousePos, hour.rect))
    {
        int hour12 = std::stoi(hour.title.text) + 1;
        hour12 = hour12 % 12;
        if (hour12 == 0)
            hour12 = 12; // Converts 0 to 12
        hour.title.text = std::to_string(hour12);
    }

    // hour.title.text = std::to_string();
    if (CheckCollisionPointRec(mousePos, minuteTens.rect))
    {
        int minute6 = std::stoi(minuteTens.title.text) + 1;
        minute6 = minute6 % 6;
        minuteTens.title.text = std::to_string(minute6);
    }

    if (CheckCollisionPointRec(mousePos, minuteOnes.rect))
    {
        int minute10 = std::stoi(minuteOnes.title.text) + 1;
        minute10 = minute10 % 10;
        minuteOnes.title.text = std::to_string(minute10);
    }
    if (CheckCollisionPointRec(mousePos, AMPM.rect))
    {
        AMPM.title.text = (AMPM.title.text == "AM" ? "PM" : "AM");
    }

    if (CheckCollisionPointRec(GetMousePosition(), alarmToggle.rect))
    {
        isOn = !isOn;
        alarmToggle.color = isOn ? DARKGREEN : RED;
        alarmToggle.title.text = (alarmToggle.title.text == "OFF" ? "ON" : "OFF");
    }
    return;
}

void Alarm::positionTimeElements()
{
    float padding = 15;
    float xOffset = rect.x + padding;

    // Position time buttons (excluding alarmToggle for now).
    std::vector<Button *> timeButtons = {&hour, &minuteTens, &minuteOnes, &AMPM};
    for (size_t i = 0; i < timeButtons.size(); i++)
    {
        timeButtons[i]->rect.x = xOffset;
        timeButtons[i]->rect.width = static_cast<float>(
                                         MeasureText(timeButtons[i]->title.text.c_str(), timeButtons[i]->title.fontSize)) +
                                     timeButtons[i]->padding;
        timeButtons[i]->rect.y = rect.y + (rect.height - timeButtons[i]->rect.height) / 2;
        timeButtons[i]->centerTitleRelative();
        timeButtons[i]->title.y = title.y;
        xOffset += timeButtons[i]->rect.width + padding;
    }

    // Position the semicolon between hour and minuteTens.
    semiColon.x = ((hour.rect.x + hour.rect.width) + minuteTens.rect.x -
                   MeasureText(semiColon.text.c_str(), semiColon.fontSize)) /
                  2;
    semiColon.y = title.y;

    // Position the alarm toggle using its dedicated init functions.
    alarmToggle.rect.x = rect.x + rect.width - (title.y - rect.y) - alarmToggle.rect.width;
    alarmToggle.rect.y = title.y;
    alarmToggle.centerTitleRelative();

    // Position MinuteOnes and MinuteTens as Combined
    minuteOnes.rect.x = minuteTens.rect.x + minuteTens.rect.width - 10;
    AMPM.rect.x = minuteOnes.rect.x + minuteOnes.rect.width + padding;

    minuteOnes.centerTitleRelative();
    minuteOnes.title.y = title.y;
    AMPM.centerTitleRelative();
}

void Alarm::drawTimeElements()
{
    // Draw the semicolon.
    DrawTextEx(GetFontDefault(), semiColon.text.c_str(),
               {static_cast<float>(semiColon.x), static_cast<float>(semiColon.y)},
               semiColon.fontSize, 1, semiColon.color);

    // Draw all time buttons including the alarm toggle.
    std::vector<Button *> timeButtons = {&hour, &minuteTens, &minuteOnes, &AMPM, &alarmToggle};
    for (auto btn : timeButtons)
    {
        btn->draw(); // Assumes Button::draw() renders its own rectangle & text.
    }
}

void Alarm::initAlarmToggle()
{
    alarmToggle.rect.height = title.fontSize - 10;
    alarmToggle.rect.width = alarmToggle.rect.height + 10;
    alarmToggle.rect.x = rect.x + rect.width - (title.y - rect.y) - alarmToggle.rect.width;
    alarmToggle.rect.y = title.y;
    alarmToggle.color = RED;

    alarmToggle.title.text = "OFF";
    alarmToggle.title.fontSize = alarmToggle.rect.width / 3;
    alarmToggle.title.x = rect.x + rect.width - (title.y - rect.y);
    alarmToggle.title.y = title.y;
}

void Alarm::draw()
{
    DrawRectangleRounded(rect, roundness, 10, color);
    title.draw();
    drawTimeElements();
}
int Alarm::getAlarmTimeInMinutes(const std::string &timeString)
{
    int hour, minute;
    char colon;
    std::string am_pm;

    std::stringstream ss(timeString);
    ss >> hour >> colon >> minute >> am_pm;

    // Convert to 24-hour format
    if (am_pm == "PM" && hour != 12)
        hour += 12;
    if (am_pm == "AM" && hour == 12)
        hour = 0;

    return hour * 60 + minute;
}

void Alarm::handleRing()
{
    std::string timeString = hour.title.text + ":" + minuteTens.title.text + minuteOnes.title.text + " " + AMPM.title.text;

    int alarmMinutes = getAlarmTimeInMinutes(timeString);
    int currentMinutes = getCurrentTimeInMinutes();

    if (alarmMinutes == currentMinutes && isOn)
    {
        if (IsMusicStreamPlaying(alarmRingtone))
            return;

        PlayMusicStream(alarmRingtone);   
    }
    StopMusicStream(alarmRingtone);
}
int Alarm::getCurrentTimeInMinutes()
{
    using namespace std::chrono;

    // Get current time point
    auto now = system_clock::now();

    // Convert to time_t to extract calendar time
    std::time_t now_c = system_clock::to_time_t(now);
    std::tm *now_tm = std::localtime(&now_c);

    // Calculate minutes since midnight
    int currentMinutes = now_tm->tm_hour * 60 + now_tm->tm_min;
    return currentMinutes;
}
