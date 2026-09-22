#include <Arduino.h>

#include "actuator_led.h"

ActuatorLed::ActuatorLed(int pinRed, int pinGreen)
    : _pinRed(pinRed),
      _pinGreen(pinGreen)
{
}

void ActuatorLed::begin()
{
    pinMode(_pinRed, OUTPUT);
    pinMode(_pinGreen, OUTPUT);

    unlit();
}

void ActuatorLed::red() const
{
    analogWrite(_pinRed, 80);
    analogWrite(_pinGreen, 0);
}

void ActuatorLed::green() const {
    analogWrite(_pinRed, 0);
    analogWrite(_pinGreen, 80);
}

void ActuatorLed::unlit() const
{
    analogWrite(_pinRed, 0);
    analogWrite(_pinGreen, 0);
}