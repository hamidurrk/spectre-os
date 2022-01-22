#include <Arduino.h>
#include "motor.h"

#define R_MTR_PWM 1
#define R_MTR_IN_1 2
#define R_MTR_IN_2 3

#define L_MTR_PWM 4
#define L_MTR_IN_1 5
#define L_MTR_IN_2 6

#define MTR_STBY 7

double motorVariables[4] = {180.0, 4.2, 0, 11.6};
double motorSpeed = motorVariables[0];
double &P = motorVariables[1];
double &I = motorVariables[2];
double &D = motorVariables[3];

void setupMotors()
{
    pinMode(R_MTR_PWM, OUTPUT);
    pinMode(R_MTR_IN_1, OUTPUT);
    pinMode(R_MTR_IN_2, OUTPUT);

    pinMode(L_MTR_PWM, OUTPUT);
    pinMode(L_MTR_IN_1, OUTPUT);
    pinMode(L_MTR_IN_2, OUTPUT);
    digitalWrite(MTR_STBY, HIGH);
}

void Forward(double del, int vel)
{
    analogWrite(R_MTR_PWM, vel);
    analogWrite(L_MTR_PWM, vel);
    digitalWrite(R_MTR_IN_1, HIGH);
    digitalWrite(R_MTR_IN_2, LOW);
    digitalWrite(L_MTR_IN_1, HIGH);
    digitalWrite(L_MTR_IN_2, LOW);
    delay(del);
}