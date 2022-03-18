#include <Arduino.h>

#define trigPin 33
#define echoPin 35

long duration;
int distance;

void sonarSetup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

double sonarSearch()
{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    return distance;
}
