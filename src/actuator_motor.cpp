#include "actuator_motor.h"
#include <Arduino.h>

ActuatorMotor::ActuatorMotor(int pin)
    : _pin(pin), _angle(-1)
{
}

void ActuatorMotor::begin()
{
    pinMode(_pin, OUTPUT);

    analogWriteFreq(50);
    analogWriteRange(20000);

    placer(0);
}

void ActuatorMotor::placer(int angle)
{
    angle = constrain(angle, 0, 180);

    int impulsion = map(angle, 0, 180, 500, 2400);

    analogWrite(_pin, impulsion);

    _angle = angle;
}

int ActuatorMotor::getAngle() const
{
    return _angle;
}