#ifndef PROJETRSP_SENSOR_ULTRASONIC_H
#define PROJETRSP_SENSOR_ULTRASONIC_H

// Mesure une distance en centimètres avec un capteur ultrasonique.
class SensorUltrasonic {
public:
    // Définit les broches de déclenchement et de réception de l'écho.
    SensorUltrasonic(int trigPin, int echoPin);

    // Configure les deux broches du capteur.
    void begin();
    // Retourne la distance ou -1 si aucun écho n'est reçu.
    float read() const;

private:
    int _trigPin;
    int _echoPin;
};

#endif