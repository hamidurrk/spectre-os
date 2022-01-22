#include <Arduino.h>
#include "motor.h"

double motorVariables[4] = {180.0, 4.2, 0, 11.6};
double &motorSpeed = motorVariables[0];
double &P = motorVariables[1];
double &I = motorVariables[2];
double &D = motorVariables[3];
