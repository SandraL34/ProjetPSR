//
// Created by Sandra Lorbois on 21/09/2026.
//

#ifndef PROJETPSR_MOTOR_H
#define PROJETPSR_MOTOR_H


class ActuatorMotor {
    public:
        ActuatorMotor(int pin);

        void begin();
        void placer(int angle);

        int getAngle() const;

    private:
        int _pin;
        int _angle;
};


#endif
