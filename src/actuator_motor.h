#ifndef PROJETRSP_MOTOR_H
#define PROJETRSP_MOTOR_H


class ActuatorMotor {
    public:
        ActuatorMotor(int pin);

        void begin();
        void move(int angle);
        void open();
        void close();

        int getAngle() const;

        bool isOpen() const;
        bool isClosed() const;

    private:
        const int _pin;
        int _angle;

        const int _angleOpen = 180;
        const int _angleClosed = 0;
};


#endif
