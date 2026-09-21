//
// Created by Sandra Lorbois on 21/09/2026.
//

#include "sensor_light.h"
#include <Arduino.h>

SensorLight::SensorLight(int pin)
    : _pin(pin)
{
}

void SensorLight::begin()
{
    pinMode(_pin, INPUT);
}

int SensorLight::lire()
{
    return analogRead(_pin);
}