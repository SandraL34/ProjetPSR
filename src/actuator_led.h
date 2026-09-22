#ifndef PROJETRSP_ACTUATOR_LED_H
#define PROJETRSP_ACTUATOR_LED_H

class ActuatorLed {
    public:
        ActuatorLed(int pinRed, int pinGreen);

        void begin();

        void red() const;
        void green() const;
        void unlit() const;

    private:
        const int _pinRed;
        const int _pinGreen;
};

#endif // PROJETRSP_ACTUATOR_LED_H