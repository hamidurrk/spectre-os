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
    CM = (duration * 0.034 / 2);
    return CM;
}

//   // Clears the trigPin
//   digitalWrite(trigPin, LOW);
//   delayMicroseconds(2);
//   // Sets the trigPin on HIGH state for 10 micro seconds
//   digitalWrite(trigPin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin, LOW);
//   // Reads the echoPin, returns the sound wave travel time in microseconds
//   duration = pulseIn(echoPin, HIGH);
//   // Calculating the distance
//   distance = duration * 0.034 / 2;
//   // Prints the distance on the Serial Monitor
//   Serial.print("Distance: ");
//   Serial.println(distance);