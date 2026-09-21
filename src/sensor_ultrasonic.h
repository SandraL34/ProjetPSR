#ifndef SENSOR_ULTRASONIC_H
#define SENSOR_ULTRASONIC_H

class SensorUltrasonic {
public:
    SensorUltrasonic(int trigPin, int echoPin);

    void begin();
    float lire();

private:
    int _trigPin;
    int _echoPin;
};

#endif