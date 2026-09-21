#include "actuator_led.h"
#include <Arduino.h>

ActuatorLed::ActuatorLed(int pinRed, int pinGreen, int pinBlue)
    : _pinRed(pinRed),
      _pinGreen(pinGreen),
      _pinBlue(pinBlue)
{
}

void ActuatorLed::begin()
{
    pinMode(_pinRed, OUTPUT);
    pinMode(_pinGreen, OUTPUT);
    pinMode(_pinBlue, OUTPUT);

    eteindre();
}

void ActuatorLed::rouge()
{
    analogWrite(_pinRed, 80);
    analogWrite(_pinGreen, 0);
    analogWrite(_pinBlue, 0);
}

void ActuatorLed::vert()
{
    analogWrite(_pinRed, 0);
    analogWrite(_pinGreen, 80);
    analogWrite(_pinBlue, 0);
}

void ActuatorLed::eteindre()
{
    analogWrite(_pinRed, 0);
    analogWrite(_pinGreen, 0);
    analogWrite(_pinBlue, 0);
}