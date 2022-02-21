#include <Arduino.h>
#include <Arduino.h>
#include "display.h"
#include "button.h"
#include "motor.h"
#include "irsensor.h"
#include "memory.h"

//------------ Global variables --------------------
extern Memory sensorMemory;
const int numOfSensors = 8;
extern unsigned int sensorThreshold[numOfSensors];

void setup()
{
  Serial.begin(9600);
  displaySetup();
  buttonSetup();
  initializeMemory(&sensorMemory);

  displayBootScreen();
}

void loop()
{
  for (int x = 0; x < 8; x++)
  {
    Serial.print(sensorThreshold[x]);
    Serial.print(" ");
  }
  Serial.println();
}