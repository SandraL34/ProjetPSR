#include <Arduino.h>

#include "actuator_led.h"

ActuatorLed::ActuatorLed(int pinRed, int pinGreen) // constructeur
    : _pinRed(pinRed),
      _pinGreen(pinGreen)
{
}

void ActuatorLed::begin() // démarrage de la led
{
    pinMode(_pinRed, OUTPUT);
    pinMode(_pinGreen, OUTPUT);

    unlit(); // éteindre la led
}

void ActuatorLed::red() const // allumer la led en rouge
{
    analogWrite(_pinRed, 80); // allumer la led rouge à 80% de son maximum
    analogWrite(_pinGreen, 0); // éteindre la led verte
}

void ActuatorLed::green() const { // allumer la led en vert
    analogWrite(_pinRed, 0); // éteindre la led rouge
    analogWrite(_pinGreen, 80); // allumer la led verte à 80% de son maximum
}

void ActuatorLed::unlit() const // éteindre les leds
{
    analogWrite(_pinRed, 0); // éteindre la led rouge
    analogWrite(_pinGreen, 0); // éteindre la led verte
}