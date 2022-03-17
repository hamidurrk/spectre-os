#include <Arduino.h>
#include "button.h"
// test
#define BTN_UP 40
#define BTN_DOWN 32
#define BTN_LEFT 38
#define BTN_RIGHT 34
#define BTN_SELECT 36

extern bool portRead(char port_type, byte pin_number);

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
    Serial.print(portRead('G', 1) );
    Serial.print("---");
    Serial.print("DOWN  ");
    Serial.print(portRead('C', 5));
    Serial.print("---");
    Serial.print("LEFT ");
    Serial.print(portRead('D', 7));
    Serial.print("---");
    Serial.print("RIGHT ");
    Serial.print(portRead('C', 3));
    Serial.print("---");
    Serial.print("SELECT ");
    Serial.println(portRead('C', 1));
}

String buttonPressed()
{
    if (portRead('G', 1) == HIGH)
    {
        return "BTN_UP";
    }
    else if (portRead('C', 5) == HIGH)
    {
        return "BTN_DOWN";
    }
    else if (portRead('C', 1) == HIGH)
    {
        return "BTN_SELECT";
    }
    else if (portRead('D', 7) == HIGH)
    {
        return "BTN_LEFT";
    }
    else if (portRead('C', 3) == HIGH)
    {
        return "BTN_RIGHT";
    }
    else
    {
        return "NO";
    }
}