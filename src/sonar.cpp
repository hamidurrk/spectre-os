#include <Arduino.h>

#define trigPin 33
#define echoPin 35

void sonarSetup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double sonarSearch()
{
    double duration = 0.00;
    double CM = 0.00;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);

    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH, 1700);
    CM = (duration / 58.82);
    return CM;
}