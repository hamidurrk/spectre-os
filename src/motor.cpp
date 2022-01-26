#include <Arduino.h>
#include "motor.h"

//-------------- Connection related---------------------------------------
#define R_MTR_PWM 12
#define R_MTR_IN_1 7
#define R_MTR_IN_2 6

#define L_MTR_PWM 2
#define L_MTR_IN_1 4
#define L_MTR_IN_2 3

#define MTR_STBY 5
//-------------------------------------------------------------------------

double motorVariables[4] = {180.0, 4.2, 0, 11.6};
double motorSpeed = motorVariables[0];
double &P = motorVariables[1];
double &I = motorVariables[2];
double &D = motorVariables[3];

//------------ External variables+functions used here-----------------
extern void readSensors();
extern void generateBinary();
//-------------------------------------------------------------------

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

void motorTest()
{
    analogWrite(R_MTR_PWM, 100);
    digitalWrite(R_MTR_IN_1, HIGH);
    digitalWrite(R_MTR_IN_2, LOW);
    delay(1000);
    analogWrite(L_MTR_PWM, 100);
    digitalWrite(L_MTR_IN_1, HIGH);
    digitalWrite(L_MTR_IN_2, LOW);
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

void Backward(double del, int vel)
{
    analogWrite(R_MTR_PWM, vel);
    analogWrite(L_MTR_PWM, vel);
    digitalWrite(R_MTR_IN_2, HIGH);
    digitalWrite(R_MTR_IN_1, LOW);
    digitalWrite(L_MTR_IN_2, HIGH);
    digitalWrite(L_MTR_IN_1, LOW);
    delay(del);
}
//--------------------------------------------------------------------------------------
void Right(double del, int vel)
{
    analogWrite(R_MTR_PWM, vel);
    analogWrite(L_MTR_PWM, vel);
    digitalWrite(R_MTR_IN_1, LOW);
    digitalWrite(L_MTR_IN_1, HIGH);
    digitalWrite(R_MTR_IN_2, HIGH);
    digitalWrite(L_MTR_IN_2, LOW);
    delay(del);
}
//--------------------------------------------------------------------------------------
void Left(double del, int vel)
{
    analogWrite(R_MTR_PWM, vel);
    analogWrite(L_MTR_PWM, vel);
    digitalWrite(R_MTR_IN_1, HIGH);
    digitalWrite(L_MTR_IN_1, LOW);
    digitalWrite(R_MTR_IN_2, LOW);
    digitalWrite(L_MTR_IN_2, HIGH);
    delay(del);
}
//---------------------------------------------------------------------------------------
void Stop(double del)
{
    analogWrite(R_MTR_PWM, 0);
    analogWrite(L_MTR_PWM, 0);
    digitalWrite(R_MTR_IN_1, LOW);
    digitalWrite(L_MTR_IN_1, LOW);
    digitalWrite(R_MTR_IN_2, LOW);
    digitalWrite(L_MTR_IN_2, LOW);
    delay(del);
}
//---------------------------------Breaking functions--------------------------------------
void BreakF()
{
    Stop(10);
    Backward(80, 250);
    Stop(10);
}
//-----------------------------------------------------------------------------------------
void BreakL()
{
    Stop(10);
    Right(50, 250);
    Stop(10);
    // Right(40, 200);
    // Stop(10);
}
//-----------------------------------------------------------------------------------------
void BreakR()
{
    Stop(10);
    Left(50, 250);
    Stop(10);
    // Left(40, 200);
    // Stop(10);
}
//----------------------------------------------------------------------------------------
void Tleft()
{
    BreakF();
    while (1)
    {
        Left(10, 240);
        readSensors();
        generateBinary();
        if (x[0] == 1 || x[1] == 1)
        {
            while (true)
            {
                Left(10, 50);
                readSensors();
                generateBinary();
                if (x[3] == 1 || x[4] == 1)
                {
                    BreakL();
                    break;
                }
            }
            break;
        }
    }
}
//----------------------------------------------------------------------------------------
void Tright()
{
    BreakF();
    while (1)
    {
        Right(10, 240);
        readSensors();
        generateBinary();
        if (x[6] == 1 || x[7] == 1)
        {
            while (true)
            {
                Right(10, 50);
                readSensors();
                generateBinary();
                if (x[3] == 1 || x[4] == 1)
                {
                    BreakR();
                    break;
                }
            }
            break;
        }
    }
}