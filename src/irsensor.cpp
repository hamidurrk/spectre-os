#include <Arduino.h>

#define IR_LED 2

boolean LED_CONTROL = true; /* put LED_CONTROL = false if you keep
"LED ON" pin disconnected */
int value[8], valueON[8], valueOFF[8];
byte sensorPin[8] = {A7, A6, A5, A4, A3, A2, A1, A0}; // arduino analog pins

// External Global Variables
extern void Forward(double del, int vel);
extern void Stop(double del);

void sensorSetup()
{
    if (LED_CONTROL)
        pinMode(IR_LED, OUTPUT);
}

void readSensor()
{
    if (LED_CONTROL)
    {
        digitalWrite(IR_LED, HIGH); // turn ON IR LEDs
        delay(20);                  // give some time to turn ON
        for (int i = 0; i <= 9; i++)
            valueON[i] =
                analogRead(sensorPin[i]);
        digitalWrite(IR_LED, LOW); // turn OFF IR LEDs
        delay(20);                 // give some time to turn OFF
        for (int i = 0; i <= 9; i++)
            valueOFF[i] =
                analogRead(sensorPin[i]);
    }
    // calculate actual sensor reading
    for (int i = 0; i <= 9; i++)
    {
        if (LED_CONTROL)
            value[i] = valueON[i] - valueOFF[i];
        else
            value[i] = analogRead(sensorPin[i]);
        Serial.print(value[i]);
        Serial.print(" ");
    }
    Serial.println(" ");
}

void generateBinary()
{

    sumation = 0;
    for (int cx = 0; cx < NumOfSensors; cx++)
    {
        if (sensor[cx] > threshold[cx])
        {
            x[cx] = 1;
        }
        else
        {
            x[cx] = 0;
        }
        sumation += x[cx];
    }

    sensorData = 0;

    for (int cxx = 0; cxx < NumOfSensors; cxx++)
    {
        sensorData = (sensorData << 1) | x[cxx];
    }
}

void generateThreshold()
{
    for (int th = 0; th < 300; th++)
    {
        Forward(1, 100);
        readSensors();
        for (int sense = 0; sense < NumOfSensors; sense++)
        {
            if (sensor[sense] > t1[sense])
                t1[sense] = sensor[sense];
            if (sensor[sense] < t2[sense])
                t2[sense] = sensor[sense];
        }
    }
    for (int thr = 0; thr < NumOfSensors; thr++)
    {
        threshold[thr] = (t1[thr] + t2[thr]) / 2;
    }
    Stop(10);
}