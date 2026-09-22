#ifndef PROJETRSP_SENSOR_LIGHT_H
#define PROJETRSP_SENSOR_LIGHT_H


class SensorLight {
    public:
        SensorLight(int pin);

        void begin();
        int read() const;

    private:
        int _pin;
};


#endif //PROJETRSP_SENSOR_LIGHT_H
