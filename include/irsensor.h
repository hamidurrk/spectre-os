#ifndef _IR_SENSOR
#define _IR_SENSOR

#include <Arduino.h>

void sensorSetup();
void readSensors();
void generateBinary();
void generateThreshold();
void showRawSensorData();
void sensorRetrieveThreshold();
bool portRead(char port_type, byte pin_number);

#endif //_IR_SENSOR