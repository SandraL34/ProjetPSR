#include "sensor_ultrasonic.h"
#include <Arduino.h>

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

float SensorUltrasonic::lire()
{
    // On envoie une impulsion de 10 µs
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    // Mesure la durée du retour
    long duree = pulseIn(_echoPin, HIGH, 30000);

    // Aucun écho reçu
    if (duree == 0)
    {
        return 2000;
    }

    // Vitesse du son ≈ 0,0343 cm/µs
    // /2 car le son fait aller + retour
    float distance = duree * 0.0343 / 2.0;

    return distance;
}