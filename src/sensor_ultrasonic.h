#ifndef PROJETRSP_SENSOR_ULTRASONIC_H
#define PROJETRSP_SENSOR_ULTRASONIC_H

class SensorUltrasonic {
public:
    SensorUltrasonic(int trigPin, int echoPin);

    void begin();
    float read() const;

private:
    int _trigPin;
    int _echoPin;
};

#endif