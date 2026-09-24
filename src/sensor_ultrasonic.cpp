#include <Arduino.h>

#include "sensor_ultrasonic.h"

SensorUltrasonic::SensorUltrasonic(int trigPin, int echoPin) // constructeur
    : _trigPin(trigPin), _echoPin(echoPin)
{
}

void SensorUltrasonic::begin() // démarrage du capteur de distance
{
    pinMode(_trigPin, OUTPUT); // broche qui trigger envoie un signal
    pinMode(_echoPin, INPUT); // broche qui echo reçoit un signal

    digitalWrite(_trigPin, LOW); // éteindre le signal trigger
}

float SensorUltrasonic::read() const { // lecture de la valeur de la distance
    digitalWrite(_trigPin, LOW); // éteindre le signal trigger
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH); // allumer le signal trigger
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW); // éteindre le signal trigger

    long duration = pulseIn(_echoPin, HIGH, 30000); // mesure de la durée de l'impulson (pour calcul distance)


    if (duration == 0) // Aucun écho reçu
    {
        return -1; // retourne une distance de -1
    }

    float distance = duration * 0.0343 / 2.0;  // conversion de la distance (Vitesse du son / 2 car aller-retour)

    return distance; // retourne la distance
}
