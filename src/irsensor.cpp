#include <Arduino.h>

const byte numOfSensors = 8;
byte i;
unsigned int sensorMaxWaitTime = 1024;
boolean firstData[numOfSensors];
unsigned int sensorRawReading[numOfSensors];
boolean sensorBinaryReading[numOfSensors];
unsigned int sensorBinaryData;

unsigned int sensorThreshold[numOfSensors];
unsigned int sensorHighestReadings[numOfSensors];
unsigned int sensorLowestReadings[numOfSensors];

byte numOfHighReadings;
//---------------------- Connection Related---------------------------------------
#define IR_LED 2
byte sensorPin[numOfSensors] = {A7, A6, A5, A4, A3, A2, A1, A0}; // arduino analog pins
//---------------------------------------------------------------------------------

// External Global Variables
extern void Forward(double del, int vel);
extern void Stop(double del);

void sensorSetup()
{
    sensorRetrieveThreshold();
}

void readSensors()
{
    /*
     * Code to read sensor data -> identical to the documentation with some simple modifications
     *
     */
    for (i = 0; i < numOfSensors; i++)
    {
        digitalWrite(sensorPin[i], HIGH);
        pinMode(sensorPin[i], OUTPUT);
    }
    delayMicroseconds(10);
    for (i = 0; i < numOfSensors; i++)
    {
        pinMode(sensorPin[i], INPUT);
        digitalWrite(sensorPin[i], LOW);
        sensorRawReading[i] = sensorMaxWaitTime;
        firstData[i] = false;
    }
    unsigned long startTime = micros();

    while (micros() - startTime < sensorMaxWaitTime)
    {
        unsigned int time = micros() - startTime;
        for (i = 0; i < numOfSensors; i++)
        {
            if ((digitalRead(sensorPin[i]) == LOW) && (firstData[i] == false))
            {
                sensorRawReading[i] = time;
                firstData[i] = true;
            }
        }
    }
}

void showRawSensorData()
{
    readSensors();
    for (i = 0; i < numOfSensors; i++)
    {
        Serial.print(sensorRawReading[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void showBinarySensorData()
{
    readSensors();
    generateBinary();
    for (i = 0; i < numOfSensors; i++)
    {
        Serial.print(sensorBinaryReading[i]);
        Serial.print(" ");
    }
    Serial.println();
}
void generateBinary()
{
    /*
     * Generates a 8 bit binary value from the sensor reading
     */
    numOfHighReadings = 0;
    sensorBinaryData = 0;
    for (int i = 0; i < numOfSensors; i++)
    {
        if (sensorRawReading[i] > sensorThreshold[i])
        {
            sensorBinaryReading[i] = 1;
            sensorBinaryData = (sensorBinaryData << 1) | 1;
        }
        else
        {
            sensorBinaryReading[i] = 0;
            sensorBinaryData = (sensorBinaryData << 1);
        }
        numOfHighReadings += sensorBinaryReading[i];
    }
}

void generateThreshold()
{
    /*
     * For generating threshold value
     */
    for (int fill_i = 0; fill_i < numOfSensors; fill_i++)
    {
        sensorHighestReadings[fill_i] = 0;
        sensorLowestReadings[fill_i] = 0;
    }
    for (int th_i = 0; th_i < 300; th_i++)
    {
        Forward(1, 100);
        readSensors();
        for (int sense = 0; sense < numOfSensors; sense++)
        {
            if (sensorRawReading[sense] > sensorHighestReadings[sense])
                sensorHighestReadings[sense] = sensorRawReading[sense];
            if (sensorRawReading[sense] < sensorLowestReadings[sense])
                sensorLowestReadings[sense] = sensorRawReading[sense];
        }
    }
    for (int thr = 0; thr < numOfSensors; thr++)
    {
        sensorThreshold[thr] = (sensorHighestReadings[thr] + sensorLowestReadings[thr]) / 2;
    }
    Stop(10);
}

void sensorRetrieveThreshold()
{
    for (i = 0; i < numOfSensors; i++)
    {
        sensorThreshold[i] = 700;
    }
}