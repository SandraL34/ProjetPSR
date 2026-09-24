#ifndef PROJETRSP_SENSOR_LIGHT_H // si le fichier n'est pas déjà inclus
#define PROJETRSP_SENSOR_LIGHT_H // inclure le fichier


class SensorLight { // constructeur
    public:
        SensorLight(int pin);

        void begin(); // fonction de démarrage
        int read() const; // fonction de lecteur de la valeur

    private: // variables internes
        int _pin;
};


#endif //PROJETRSP_SENSOR_LIGHT_H
