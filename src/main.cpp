#include <Arduino.h>

#include "actuator_motor.h"
#include "actuator_led.h"
#include "sensor_light.h"
#include "sensor_ultrasonic.h"


// Pin ESP

const int PIN_LIGHT_SENSOR = A0;
const int PIN_MOTOR = 14;

const int PIN_LED_RED = D1;
const int PIN_LED_GREEN  = D2;

const int PIN_TRIG = D6;
const int PIN_ECHO = D7;


// Seuils

const int LIMIT_LIGHT = 1000;
const int LIMIT_DARK = 800;

const int LIMIT_DISTANCE_DANGER = 50;


// Création des composants

SensorLight lightSensor(PIN_LIGHT_SENSOR);

ActuatorMotor arm(PIN_MOTOR);

SensorUltrasonic distance(PIN_TRIG, PIN_ECHO);

ActuatorLed led(PIN_LED_RED, PIN_LED_GREEN);


// Setup

void setup()
{
    Serial.begin(115200);

    lightSensor.begin();
    arm.begin();
    distance.begin();
    led.begin();

    Serial.println();
    Serial.println("Systeme pret");
}


// Loop

void loop()
{
    int lightValue = lightSensor.read();
    float distanceValue = distance.read();

    // S'il y a un obstacle et qu'il est à une distance trop proche
    if (distanceValue != -1 && distanceValue < LIMIT_DISTANCE_DANGER)
    {
        // Si le bras est déployé, on le replie et on allume la LED rouge

        if (arm.isOpen())
        {
            led.red();

            arm.close();

            Serial.println("Repli du bras car obstacle");
        }
    }
    // S'il n'y a pas d'obstacle proche
    else
    {
        // Si le bras n'est pas déployé et qu'il y a assez de lumière, on le déploie et on allume la led verte

        if (lightValue > LIMIT_LIGHT && arm.isClosed())
        {

            led.green();

            arm.open();

            Serial.println("Déploiement du bras car lumière");
        }


        // Si le bras est déployé et qu'il n'y a plus de lumière, on le replie et on allume la led rouge

        else if (lightValue < LIMIT_DARK && arm.isOpen())
        {
            led.red();

            arm.close();

            Serial.println("Repli du bras car obscurité");
        }
    }


    // Display


    delay(1500);

    Serial.print("Lumiere : ");
    Serial.print(lightValue);

    Serial.print(" | Bras : ");
    Serial.print(arm.getAngle());

    Serial.print(" | Distance : ");
    Serial.print(distanceValue);
    Serial.println();

    led.unlit();
}