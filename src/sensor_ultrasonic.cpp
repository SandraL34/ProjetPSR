#include <Arduino.h>

#include "sensor_ultrasonic.h"

SensorUltrasonic::SensorUltrasonic(int trigPin, int echoPin)
    : _trigPin(trigPin), _echoPin(echoPin)
{
}

void SensorUltrasonic::begin()
{
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);

    digitalWrite(_trigPin, LOW);
}

float SensorUltrasonic::read() const {
    digitalWrite(_trigPin, LOW); // init
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH, 30000);

    // Aucun écho reçu
    if (duration == 0)
    {
        return -1;
    }

    float distance = duration * 0.0343 / 2.0;  // Vitesse du son / 2 car aller-retour

    return distance;
}
