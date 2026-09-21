#include <Arduino.h>

#include "actuator_motor.h"
#include "actuator_led.h"
#include "sensor_light.h"
#include "sensor_ultrasonic.h"

// =========================
// Broches
// =========================

const int PIN_CAPTEUR = A0;
const int PIN_SERVO = 14;

// LED RGB
const int PIN_LED_ROUGE = D1;
const int PIN_LED_VERT  = D2;
const int PIN_LED_BLEU  = D3;

// HC-SR04
const int PIN_TRIG = D6;
const int PIN_ECHO = D7;


// =========================
// Seuils
// =========================

// Lumière
const int SEUIL_LUMIERE = 1000;
const int SEUIL_SOMBRE = 800;

// Distance
const int SEUIL_DISTANCE_DANGER = 50;


// =========================
// Création des composants
// =========================

SensorLight capteurLumiere(PIN_CAPTEUR);

ActuatorMotor bras(PIN_SERVO);

SensorUltrasonic distance(PIN_TRIG, PIN_ECHO);

ActuatorLed led(
    PIN_LED_ROUGE,
    PIN_LED_VERT,
    PIN_LED_BLEU
);


// =========================
// Setup
// =========================

void setup()
{
    Serial.begin(115200);

    capteurLumiere.begin();
    bras.begin();
    distance.begin();
    led.begin();

    Serial.println();
    Serial.println("Systeme pret");
}


// =========================
// Loop
// =========================

void loop()
{
    // Lecture des capteurs
    int lumiere = capteurLumiere.lire();
    float valeurDistance = distance.lire();


    // =========================================
    // OBSTACLE
    // =========================================

    if (valeurDistance != -1 &&
        valeurDistance < SEUIL_DISTANCE_DANGER)
    {
        // Si le bras est déployé,
        // on le replie et on allume la LED rouge

        if (bras.getAngle() != 0)
        {
            led.rouge();

            bras.placer(0);

            Serial.println("Obstacle -> bras replie");
        }
    }


    // =========================================
    // PAS D'OBSTACLE
    // =========================================

    else
    {
        // -------------------------
        // Lumière -> déploiement
        // -------------------------

        if (lumiere > SEUIL_LUMIERE &&
            bras.getAngle() != 180)
        {
            led.vert();

            bras.placer(180);

            Serial.println("Lumiere -> bras deploye");
        }


        // -------------------------
        // Obscurité -> repliement
        // -------------------------

        else if (lumiere < SEUIL_SOMBRE &&
                 bras.getAngle() != 0)
        {
            led.rouge();

            bras.placer(0);

            Serial.println("Obscurite -> bras replie");
        }
    }


    // =========================================
    // Affichage
    // =========================================


    delay(1500);

    Serial.print("Lumiere : ");
    Serial.print(lumiere);

    Serial.print(" | Bras : ");
    Serial.print(bras.getAngle());

    Serial.print(" | Distance : ");
    Serial.print(valeurDistance);
    Serial.println(" cm");

    led.eteindre();
}