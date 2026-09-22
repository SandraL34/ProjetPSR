#include <Arduino.h>

#include "sensor_light.h"


SensorLight::SensorLight(int pin)
    : _pin(pin)
{
}

void SensorLight::begin()
{
    pinMode(_pin, INPUT);
}

int SensorLight::read() const
{
    return analogRead(_pin);
}