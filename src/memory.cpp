#include <Arduino.h>
#include <EEPROM.h>
#include "memory.h"

const int memoryLength = 500;
int memoryArray[memoryLength];
Memory sensorMemory;

//------------- External Global Variables -------------------------
extern float motorVariables[4];
const int numOfSensors = 8;
extern unsigned int sensorThreshold[numOfSensors];

void initializeMemory(struct Memory *m)
{
    m->size = memoryLength;
    m->position = 0;
    m->arr = memoryArray;
    for (int i = 0; i < m->size; i++)
    {
        m->arr[i] = 0;
    }
}
void memoryShowData(struct Memory *m)
{
    for (int i = m->position + 1; i <= m->size + m->position; i++)
    {
        Serial.println(m->arr[i % m->size]);
    }
}

void memoryAddReading(struct Memory *m, int reading)
{
    m->position = (m->position + 1) % m->size;
    m->arr[m->position] = reading;
}

void memorySaveMotorVariables()
{
    for (int i = 0; i < 4; i++)
    {
        EEPROM.put(i * (sizeof(float)), motorVariables[i]);
    }
}

void memoryRetrieveMotorVariables()
{
    for (int i = 0; i < 4; i++)
    {
        EEPROM.get(i * (sizeof(float)), motorVariables[i]);
    }
}
void memorySaveSensorVariables()
{
    for (int i = 0; i < numOfSensors; i++)
    {
        EEPROM.put(16 + (i * (sizeof(int))), sensorThreshold[i]);
    }
}

void memoryRetrieveSensorVariables()
{
    for (int i = 0; i < numOfSensors; i++)
    {
        EEPROM.get(i * (sizeof(int)), sensorThreshold[i]);
    }
}