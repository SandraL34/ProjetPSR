#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "actuator_motor.h"
#include "actuator_led.h"
#include "sensor_light.h"
#include "sensor_ultrasonic.h"
#include "api_client.h"


// Envoi API
const char* WIFI_SSID = "Xiaomi 11 Lite 5G NE";
const char* WIFI_PASSWORD = "vf8t5ukb8t258f2";

const char* API_URL = "http://10.213.28.43:8000/api/measurements";
const char* API_USERNAME = "test@gmail.com";
const char* API_PASSWORD = "test";

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

const int LIMIT_DISTANCE_DANGER = 5;


// Création des composants

SensorLight lightSensor(PIN_LIGHT_SENSOR);

ActuatorMotor arm(PIN_MOTOR);

SensorUltrasonic distance(PIN_TRIG, PIN_ECHO);

ActuatorLed led(PIN_LED_RED, PIN_LED_GREEN);

ApiClient apiClient(API_URL, API_USERNAME, API_PASSWORD);

ESP8266WebServer server(80);


// Connect wifi

void connectWifi()
{
    Serial.print("Connexion au Wi-Fi");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Wi-Fi connecté !");
    Serial.print("Adresse IP de l'ESP : ");
    Serial.println(WiFi.localIP());
}

// ajouter les headers pour la connexion manuelle à L'ESP

void addCorsHeaders()
{
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// Requête options

void handleOptions()
{
    addCorsHeaders();
    server.send(204);
}

// Créer serveur web pour commandes manuelles

void handleCommand()
{
    addCorsHeaders();

    if (!server.hasArg("plain"))
    {
        server.send(
            400,
            "application/json",
            "{\"success\":false,\"message\":\"Body JSON manquant\"}"
        );
        return;
    }

    String body = server.arg("plain");

    Serial.print("Commande reçue : ");
    Serial.println(body);

    if (body.indexOf("\"action\":\"deploy\"") >= 0)
    {
        if (arm.isClosed())
        {
            led.green();
            arm.open();

            Serial.println("Commande manuelle : DEPLOY");
        }
        else
        {
            Serial.println("Commande DEPLOY : bras déjà ouvert");
        }

        server.send(
            200,
            "application/json",
            "{\"success\":true,\"action\":\"deploy\"}"
        );
        return;
    }

    if (body.indexOf("\"action\":\"retract\"") >= 0)
    {
        if (arm.isOpen())
        {
            led.red();
            arm.close();

            Serial.println("Commande manuelle : RETRACT");
        }
        else
        {
            Serial.println("Commande RETRACT : bras déjà fermé");
        }

        server.send(
            200,
            "application/json",
            "{\"success\":true,\"action\":\"retract\"}"
        );
        return;
    }

    server.send(
        400,
        "application/json",
        "{\"success\":false,\"message\":\"Action inconnue\"}"
    );
}

// Setup

void setup()
{
    server.on("/api/command", HTTP_POST, handleCommand);
    server.on("/api/command", HTTP_OPTIONS, handleOptions);
    
    Serial.begin(115200);

    connectWifi();

    lightSensor.begin();
    arm.begin();
    distance.begin();
    led.begin();

    server.begin();

    Serial.println();
    Serial.println("Systeme pret");
    Serial.println("Serveur HTTP demarre");
}


// Loop

void loop()
{
    server.handleClient();

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

    bool panelOpen = arm.isOpen();

    apiClient.sendMeasurement(lightValue, distanceValue, panelOpen);

    // Display

    server.handleClient();
    delay(1500);
    server.handleClient();

    Serial.print("Lumiere : ");
    Serial.print(lightValue);

    Serial.print(" | Bras : ");
    Serial.print(arm.getAngle());

    Serial.print(" | Distance : ");
    Serial.print(distanceValue);
    Serial.println();

    led.unlit();
}