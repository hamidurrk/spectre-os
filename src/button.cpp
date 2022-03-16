#include <Arduino.h>
#include "button.h"
// test
#define BTN_UP 14
#define BTN_DOWN 16
#define BTN_LEFT 15
#define BTN_RIGHT 18
#define BTN_SELECT 17

void buttonSetup()
{
    pinMode(BTN_UP, INPUT);
    pinMode(BTN_DOWN, INPUT);
    pinMode(BTN_RIGHT, INPUT);
    pinMode(BTN_LEFT, INPUT);
    pinMode(BTN_SELECT, INPUT);
}

void buttonTest()
{
    Serial.print("UP ");
    Serial.print(digitalRead(BTN_UP));
    Serial.print("---");
    Serial.print("DOWN  ");
    Serial.print(digitalRead(BTN_DOWN));
    Serial.print("---");
    Serial.print("LEFT ");
    Serial.print(digitalRead(BTN_LEFT));
    Serial.print("---");
    Serial.print("RIGHT ");
    Serial.print(digitalRead(BTN_RIGHT));
    Serial.print("---");
    Serial.print("SELECT ");
    Serial.println(digitalRead(BTN_SELECT));
}

String buttonPressed()
{
    if (digitalRead(BTN_UP) == HIGH)
    {
        return "BTN_UP";
    }
    else if (digitalRead(BTN_DOWN) == HIGH)
    {
        return "BTN_DOWN";
    }
    else if (digitalRead(BTN_SELECT) == HIGH)
    {
        return "BTN_SELECT";
    }
    else if (digitalRead(BTN_LEFT) == HIGH)
    {
        return "BTN_LEFT";
    }
    else if (digitalRead(BTN_RIGHT) == HIGH)
    {
        return "BTN_RIGHT";
    }
    else
    {
        return "NO";
    }
}