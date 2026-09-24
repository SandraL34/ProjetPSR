#include <Arduino.h>

#include "sensor_ultrasonic.h"

SensorUltrasonic::SensorUltrasonic(int trigPin, int echoPin)
    : _trigPin(trigPin), _echoPin(echoPin)
{
    // Mémorise les broches utilisées pour déclencher le capteur et recevoir son écho.
}

void SensorUltrasonic::begin()
{
    // Prépare les directions électriques et place la broche de déclenchement au repos.
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);

    digitalWrite(_trigPin, LOW);
}

float SensorUltrasonic::read() const {
    // Génère une impulsion de 10 microsecondes pour lancer une mesure ultrasonique.
    digitalWrite(_trigPin, LOW); // init
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    // Mesure la durée du retour, avec un délai maximal d'environ 30 ms.
    long duration = pulseIn(_echoPin, HIGH, 30000);

    // Aucun écho reçu
    if (duration == 0)
    {
        return -1;
    }

    // Convertit le temps aller-retour en centimètres en divisant par deux.
    float distance = duration * 0.0343 / 2.0;  // Vitesse du son / 2 car aller-retour

    return distance;
}
