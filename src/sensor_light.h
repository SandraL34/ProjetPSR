//
// Created by Sandra Lorbois on 21/09/2026.
//

#ifndef PROJETPSR_SENSOR_LIGHT_H
#define PROJETPSR_SENSOR_LIGHT_H


class SensorLight {
    public:
        SensorLight(int pin);

        void begin();
        int lire();

    private:
        int _pin;
};


#endif //PROJETPSR_SENSOR_LIGHT_H
