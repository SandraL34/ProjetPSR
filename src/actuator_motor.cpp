#include <Arduino.h>

#include "actuator_motor.h"

ActuatorMotor::ActuatorMotor(int pin) // constructeur
    : _pin(pin), _angle(-1)
{
}

void ActuatorMotor::begin() // démarrage du bras moteur
{
    pinMode(_pin, OUTPUT); // la broche va envoyer un signal

    analogWriteFreq(50); // réglage de la fréquence (un signal complet dure 1 / 50 = 0,02 secondes)
    analogWriteRange(20000); // résolution du signal (correspondance analogWrite vs microsecondes)

    move(_angleClosed); // repli du bras
}

void ActuatorMotor::move(int angle) // déplacement du bras
{
    angle = constrain(angle, 0, 180); // range maximum du bras

    int impulsion = map(angle, 0, 180, 500, 2400); // conversion de l'angle en µs

    analogWrite(_pin, impulsion); // envoi du signal et donc mouvement du bras

    _angle = angle; // donner à la variable la valeur de l'attribut
}

void ActuatorMotor::open() // déploiement du bras
{
    move(_angleOpen); // déployer le bras
}

void ActuatorMotor::close() // repli du bras
{
    move(_angleClosed); // replier le bras
}

bool ActuatorMotor::isOpen() const // récupérer l'angle si déployé
{
    return _angle == _angleOpen; // retourner l'angle
}

bool ActuatorMotor::isClosed() const // récupérer l'angle si replié
{
    return _angle == _angleClosed; // retourner l'angle
}

int ActuatorMotor::getAngle() const // Retourner l'angle
{
    return _angle; // Retourner l'angle
}