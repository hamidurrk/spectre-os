#include <Arduino.h>

#define trigPin 35
#define echoPin 33

void sonarSetup()
{
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
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