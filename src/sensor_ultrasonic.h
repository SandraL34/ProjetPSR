#ifndef PROJETRSP_SENSOR_ULTRASONIC_H // si le fichier n'est pas déjà inclus
#define PROJETRSP_SENSOR_ULTRASONIC_H // inclure le fichier

class SensorUltrasonic { // constructeur
public:
    SensorUltrasonic(int trigPin, int echoPin);

    void begin(); // fonction de démarrage
    float read() const; // fonction de lecture de la valeur

private: // variables internes
    int _trigPin;
    int _echoPin;
};

#endif