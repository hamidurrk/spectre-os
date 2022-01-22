#include <Arduino.h>
#include <Arduino.h>
#include "display.h"
#include "button.h"
#include "motor.h"

void setup()
{
  Serial.begin(9600);
  // displaySetup();
  // buttonSetup();
  setupMotors();
  // displayBootScreen();
}

void loop()
{
  Forward(100, 100);
  Serial.println("Forward");
}