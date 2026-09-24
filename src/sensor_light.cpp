#include <Arduino.h>

#include "sensor_light.h"


SensorLight::SensorLight(int pin)
    : _pin(pin)
{
    // Conserve la broche analogique reliée au capteur de luminosité.
}

void SensorLight::begin()
{
    // Configure la broche en entrée pour permettre la lecture de la tension du capteur.
    pinMode(_pin, INPUT);
}

int SensorLight::read() const
{
    // Retourne la valeur brute du convertisseur analogique de l'ESP8266.
    return analogRead(_pin);
}