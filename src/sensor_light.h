#ifndef PROJETRSP_SENSOR_LIGHT_H
#define PROJETRSP_SENSOR_LIGHT_H


// Encapsule la lecture analogique du capteur de luminosité.
class SensorLight {
    public:
        // Associe le capteur à sa broche analogique.
        SensorLight(int pin);

        // Configure la broche du capteur.
        void begin();
        // Retourne la valeur brute du convertisseur analogique.
        int read() const;

    private:
        int _pin;
};


#endif //PROJETRSP_SENSOR_LIGHT_H
