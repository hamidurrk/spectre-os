#include <Arduino.h>
#include "motor.h"

//-------------- Connection related---------------------------------------
#define R_MTR_PWM 7
#define R_MTR_IN_1 5
#define R_MTR_IN_2 6

#define L_MTR_PWM 2
#define L_MTR_IN_1 4
#define L_MTR_IN_2 3

#define MTR_STBY 5

#define LED_1 48
#define LED_2 50

//-------------------------------------------------------------------------

float motorVariables[4] = {80.0, 4.2, 0, 11.6};
float &motorSpeed = motorVariables[0];
float &P = motorVariables[1];
float &I = motorVariables[2];
float &D = motorVariables[3];
const byte numOfSensors = 8;
int R_motorSpeed = motorSpeed;
int L_motorSpeed = motorSpeed;
//------------ External variables+functions used here-----------------
extern void readSensors();
extern void generateBinary();
extern boolean sensorBinaryReading[numOfSensors];
extern String buttonPressed();
extern void memoryRetrieveMotorVariables();
extern void PIDval();
extern void deviation();
extern double PIDvalue;
extern double Vul;
extern byte numOfHighReadings;
//-------------------------------------------------------------------

void motorSetup()
{
    pinMode(R_MTR_PWM, OUTPUT);
    pinMode(R_MTR_IN_1, OUTPUT);
    pinMode(R_MTR_IN_2, OUTPUT);

    pinMode(L_MTR_PWM, OUTPUT);
    pinMode(L_MTR_IN_1, OUTPUT);
    pinMode(L_MTR_IN_2, OUTPUT);
    digitalWrite(MTR_STBY, HIGH);
    memoryRetrieveMotorVariables();
}
//---------------------------------------------------------------------------------------
void motorTestAuto()
{
    // Motor Forward Test
    analogWrite(R_MTR_PWM, 100);
    digitalWrite(R_MTR_IN_1, HIGH);
    digitalWrite(R_MTR_IN_2, LOW);
    delay(1000);

    // digitalWrite(R_MTR_IN_1, LOW);
    // digitalWrite(R_MTR_IN_2, LOW);

    // analogWrite(L_MTR_PWM, 100);
    // digitalWrite(L_MTR_IN_1, HIGH);
    // digitalWrite(L_MTR_IN_2, LOW);
    // delay(1000);
    // digitalWrite(L_MTR_IN_1, LOW);
    // digitalWrite(L_MTR_IN_2, LOW);

    // // Motor backward test
    // analogWrite(R_MTR_PWM, 100);
    // digitalWrite(R_MTR_IN_1, LOW);
    // digitalWrite(R_MTR_IN_2, HIGH);
    // delay(1000);
    // digitalWrite(R_MTR_IN_1, LOW);
    // digitalWrite(R_MTR_IN_2, LOW);

    // analogWrite(L_MTR_PWM, 100);
    // digitalWrite(L_MTR_IN_1, LOW);
    // digitalWrite(L_MTR_IN_2, HIGH);
    // delay(1000);
    // digitalWrite(L_MTR_IN_1, LOW);
    // digitalWrite(L_MTR_IN_2, LOW);

    // delay(100);
}
//---------------------------------------------------------------------------------------
void motorCalibrate()
{
    while (true)
    {
        analogWrite(R_MTR_PWM, R_motorSpeed);
        analogWrite(L_MTR_PWM, L_motorSpeed);
        digitalWrite(R_MTR_IN_1, HIGH);
        digitalWrite(R_MTR_IN_2, LOW);
        digitalWrite(L_MTR_IN_1, HIGH);
        digitalWrite(L_MTR_IN_2, LOW);
        delay(50);
        if (buttonPressed() != "NO")
            break;
    }
}
//----------------------------------------------------------------------------------------
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
// //---------------------------------Breaking functions--------------------------------------
void BreakF()
{
    for (int i = 100; i >= 0; i -= 5)
    {
        Forward(1, i);
    }
    Stop(20);
}
// //-----------------------------------------------------------------------------------------
void BreakL()
{
    for (int i = 100; i >= 0; i -= 5)
    {
        Left(1, i);
    }
    Stop(20);
}
// //-----------------------------------------------------------------------------------------
void BreakR()
{
    for (int i = 100; i >= 0; i -= 5)
    {
        Right(1, i);
    }
    Stop(20);
}
//------------------------------Sharp Turn Functions------------------------------------------
void Tleft()
{
    BreakF();
    while (1)
    {
        Left(10, 240);
        readSensors();
        generateBinary();
        if (sensorBinaryReading[0] == 1 || sensorBinaryReading[1] == 1)
        {
            while (true)
            {
                Left(10, 50);
                readSensors();
                generateBinary();
                if (sensorBinaryReading[3] == 1 || sensorBinaryReading[4] == 1)
                {
                    BreakL();
                    break;
                }
            }
            break;
        }
    }
}
// //----------------------------------------------------------------------------------------
void Tright()
{
    BreakF();
    while (1)
    {
        Right(10, 240);
        readSensors();
        generateBinary();
        if (sensorBinaryReading[6] == 1 || sensorBinaryReading[7] == 1)
        {
            while (true)
            {
                Right(10, 50);
                readSensors();
                generateBinary();
                if (sensorBinaryReading[3] == 1 || sensorBinaryReading[4] == 1)
                {
                    BreakR();
                    break;
                }
            }
            break;
        }
    }
}

void doura()
{
    if (Vul > 0)
    {
        R_motorSpeed = motorSpeed - PIDvalue;
        L_motorSpeed = motorSpeed;
    }
    else if (Vul < 0)
    {
        L_motorSpeed = motorSpeed + PIDvalue;
        R_motorSpeed = motorSpeed;
    }
    else
    {
        R_motorSpeed = motorSpeed;
        L_motorSpeed = motorSpeed;
    }

    if (R_motorSpeed < 5)
        R_motorSpeed = 5;
    if (L_motorSpeed < 5)
        L_motorSpeed = 5;

    analogWrite(R_MTR_PWM, R_motorSpeed);
    analogWrite(L_MTR_PWM, L_motorSpeed);
    digitalWrite(R_MTR_IN_1, HIGH);
    digitalWrite(L_MTR_IN_1, HIGH);
    digitalWrite(R_MTR_IN_2, LOW);
    digitalWrite(L_MTR_IN_2, LOW);
}

void Run()
{
    readSensors();
    generateBinary();
    deviation();
    PIDval();
    doura();
    if (numOfHighReadings == 0 || numOfHighReadings >= 4)
    {
        detection();
    }
}

void detection()
{
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    for (int detect = 0; detect < 20; detect++)
    {
        readSensors();
        generateBinary();
        deviation();
        PIDval();
        doura();
    }
}