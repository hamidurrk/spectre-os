#include <Arduino.h>
#include <Arduino.h>
#include "display.h"
#include "button.h"
#include "motor.h"
#include "irsensor.h"
#include "memory.h"

// Abandoned Project :)
//------------ Global variables --------------------
extern struct Memory sensorMemory;
const int numOfSensors = 8;
extern unsigned int sensorThreshold[numOfSensors];
extern float motorVariables[4];

void setup()
{
  Serial.begin(9600);
  displaySetup();
  buttonSetup();
  memorySetup(&sensorMemory);

  // Only Once needed
  // memorySaveMotorVariables();
  // memorySaveSensorVariables();

  sensorSetup();
  motorSetup();

  displayBootScreen();
  //------------------------------------------------------------
  generateThreshold();



}

void loop()
{
  displayMenu("MAIN_MENU")
  // readSensors();
  // generateBinary();
  // showBinarySensorData();
}