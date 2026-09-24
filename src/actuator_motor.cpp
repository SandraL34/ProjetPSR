#include <Arduino.h>

#include "actuator_motor.h"

ActuatorMotor::ActuatorMotor(int pin)
    : _pin(pin), _angle(-1)
{
    // Conserve la broche de commande et marque la position comme inconnue au démarrage.
}

void ActuatorMotor::begin()
{
    // Configure le signal PWM du servomoteur puis le place en position initiale.
    pinMode(_pin, OUTPUT);

    analogWriteFreq(50); // un signal complet dure 1 / 50 = 0,02 secondes
    analogWriteRange(20000); // correspondance analogWrite vs microsecondes

    move(0);
}

void ActuatorMotor::move(int angle)
{
    // Limite l'angle et le convertit en largeur d'impulsion acceptée par le servo.
    angle = constrain(angle, 0, 180);

    int impulsion = map(angle, 0, 180, 500, 2400); // conversion de l'angle en µs

    analogWrite(_pin, impulsion);

    _angle = angle;
}

void ActuatorMotor::open()
{
    // Déplace le bras vers l'angle prédéfini correspondant à l'ouverture.
    move(_angleOpen);
}

void ActuatorMotor::close()
{
    // Déplace le bras vers l'angle prédéfini correspondant à la fermeture.
    move(_angleClosed);
}

bool ActuatorMotor::isOpen() const
{
    // Compare la dernière position connue à la position ouverte.
    return _angle == _angleOpen;
}

bool ActuatorMotor::isClosed() const
{
    // Compare la dernière position connue à la position fermée.
    return _angle == _angleClosed;
}

int ActuatorMotor::getAngle() const
{
    return _angle;
}