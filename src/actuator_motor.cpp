#include <Arduino.h>

#include "actuator_motor.h"

ActuatorMotor::ActuatorMotor(int pin)
    : _pin(pin), _angle(-1)
{
}

void ActuatorMotor::begin()
{
    pinMode(_pin, OUTPUT);

    analogWriteFreq(50); // un signal complet dure 1 / 50 = 0,02 secondes
    analogWriteRange(20000); // correspondance analogWrite vs microsecondes

    move(0);
}

void ActuatorMotor::move(int angle)
{
    angle = constrain(angle, 0, 180);

    int impulsion = map(angle, 0, 180, 500, 2400); // conversion de l'angle en µs

    analogWrite(_pin, impulsion);

    _angle = angle;
}

void ActuatorMotor::open()
{
    move(_angleOpen);
}

void ActuatorMotor::close()
{
    move(_angleClosed);
}

bool ActuatorMotor::isOpen() const
{
    return _angle == _angleOpen;
}

bool ActuatorMotor::isClosed() const
{
    return _angle == _angleClosed;
}

int ActuatorMotor::getAngle() const
{
    return _angle;
}