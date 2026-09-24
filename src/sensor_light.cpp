#include <Arduino.h>

#include "sensor_light.h"


SensorLight::SensorLight(int pin) // constructeur
    : _pin(pin)
{
}

void SensorLight::begin() // démarrage du capteur de luminosité
{
    pinMode(_pin, INPUT); // la broche va recevoir un signal
}

int SensorLight::read() const // lecture de la valeur de la luminosité
{
    return analogRead(_pin); // retourne la valeur de la luminosité
}