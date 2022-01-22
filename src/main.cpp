#include <Arduino.h>
#include <Arduino.h>
#include "display.h"
#include "button.h"
#include "motor.h"
void setup()
{
  Serial.begin(9600);
  displaySetup();
  buttonSetup();

  displayBootScreen();
}

void loop()
{

  int size = sizeof(uint8_t);
  Serial.println(size);
}