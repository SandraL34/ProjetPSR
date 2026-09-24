#include <Arduino.h>

#include "actuator_led.h"

ActuatorLed::ActuatorLed(int pinRed, int pinGreen)
    : _pinRed(pinRed),
      _pinGreen(pinGreen)
{
    // Conserve les deux broches utilisées pour afficher l'état du panneau.
}

void ActuatorLed::begin()
{
    // Configure les LED et les éteint avant toute décision automatique.
    pinMode(_pinRed, OUTPUT);
    pinMode(_pinGreen, OUTPUT);

    unlit();
}

void ActuatorLed::red() const
{
    // Allume uniquement la LED rouge pour signaler un repli ou un danger.
    analogWrite(_pinRed, 80);
    analogWrite(_pinGreen, 0);
}

void ActuatorLed::green() const {
    // Allume uniquement la LED verte pour signaler un panneau déployé.
    analogWrite(_pinRed, 0);
    analogWrite(_pinGreen, 80);
}

void ActuatorLed::unlit() const
{
    // Coupe les deux sorties lorsqu'aucun état lumineux ne doit rester affiché.
    analogWrite(_pinRed, 0);
    analogWrite(_pinGreen, 0);
}