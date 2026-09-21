#ifndef PROJETPSR_ACTUATOR_LED_H
#define PROJETPSR_ACTUATOR_LED_H

class ActuatorLed {
    public:
        ActuatorLed(int pinRed, int pinGreen, int pinBlue);

        void begin();

        void rouge();
        void vert();
        void eteindre();

    private:
        int _pinRed;
        int _pinGreen;
        int _pinBlue;
};

#endif // PROJETPSR_ACTUATOR_LED_H