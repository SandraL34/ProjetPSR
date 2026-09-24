#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

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
const char* MDNS_HOSTNAME = "rsp-panel";

// Définition des broches de l'ESP

const int PIN_LIGHT_SENSOR = A0;
const int PIN_MOTOR = 14;

const int PIN_LED_RED = D1;
const int PIN_LED_GREEN  = D2;

const int PIN_TRIG = D6;
const int PIN_ECHO = D7;


// Seuils

const int LIMIT_LIGHT = 1000; // déployer
const int LIMIT_DARK = 800; // replier

const int LIMIT_DISTANCE_DANGER = 5; // replier


// Création des objets

SensorLight lightSensor(PIN_LIGHT_SENSOR);

ActuatorMotor arm(PIN_MOTOR);

SensorUltrasonic distance(PIN_TRIG, PIN_ECHO);

ActuatorLed led(PIN_LED_RED, PIN_LED_GREEN);

ApiClient apiClient(API_URL, API_USERNAME, API_PASSWORD);

ESP8266WebServer server(80);


// Mode manuel

bool manualMode = false;


// Connect wifi

void connectWifi()
{
    Serial.print("Connexion au Wi-Fi");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // démarrer le wifi

    while (WiFi.status() != WL_CONNECTED) // Tant que le wifi n'est pas connecté
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Wi-Fi connecté !");
    Serial.print("Adresse IP de l'ESP : ");
    Serial.println(WiFi.localIP());
}

// ajouter les headers pour la connexion manuelle à L'ESP (cors = mécanisme de sécurité via headers de sécurité)

void addCorsHeaders()
{
    server.sendHeader("Access-Control-Allow-Origin", "*"); // toutes les IP sont autorisées
    server.sendHeader("Access-Control-Allow-Methods", "POST, OPTIONS"); //  requêtes post et options autorisées
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type"); // Accepter comme header "content-type"
}

// Requête options

void handleOptions() // envoi des headers
{
    addCorsHeaders(); // ajouter les headers pour la connexion manuelle à L'ESP
    server.send(204); // HTTP success no content
}

void handleHealth() // envoi de l'état de l'appareil
{
    addCorsHeaders(); // ajouter les headers pour la connexion manuelle à L'ESP
    server.send(200, "application/json", "{\"ok\":true,\"service\":\"rsp-panel\"}"); // requête OK renvoyée en JSON
}

// Créer serveur web pour commandes manuelles

void handleCommand()
{
    addCorsHeaders(); // ajouter les headers pour la connexion manuelle à L'ESP

    if (!server.hasArg("plain")) // si la requête n'a pas de body
    {
        server.send(
            400,
            "application/json",
            "{\"success\":false,\"message\":\"Body JSON manquant\"}"
        ); // requête failed renvoyée en json
        return;
    }

    String body = server.arg("plain"); // récupération du body
    String command = body; // copie du body
    command.replace(" ", ""); // supprime les espaces
    command.replace("\t", ""); // supprime les tabs
    command.replace("\r", ""); // supprime les retours charriot
    command.replace("\n", ""); // supprime les sauts de ligne

    Serial.print("Commande reçue : ");
    Serial.println(body);

    if (command.indexOf("\"action\":\"deploy\"") >= 0) // si la commande deploy est reçue
    {
        manualMode = true; // passage en mode manuel
        if (arm.isClosed()) // si le bras est replié
        {
            led.green(); // allume la led verte
            arm.open(); // déplie le bras

            Serial.println("Commande manuelle : DEPLOY");
        }
        else // si le bras est déjà déplié
        {
            Serial.println("Commande DEPLOY : bras déjà ouvert");
        }

        server.send(
            200,
            "application/json",
            "{\"success\":true,\"action\":\"deploy\",\"panel_open\":true,\"mode\":\"manual\"}"
        ); // requête OK renvoyée en JSON
        return;
    }

    if (command.indexOf("\"action\":\"retract\"") >= 0) // si la commande retract est reçue
    {
        manualMode = true; // passage en mode manuel
        if (arm.isOpen()) // si le bras est ouvert
        {
            led.red(); // allume la led rouge
            arm.close(); // replie le bras

            Serial.println("Commande manuelle : RETRACT");
        }
        else // si le bras est déjà replié
        {
            Serial.println("Commande RETRACT : bras déjà fermé");
        }

        server.send(
            200,
            "application/json",
            "{\"success\":true,\"action\":\"retract\",\"panel_open\":false,\"mode\":\"manual\"}"
        ); // requête OK renvoyée par JSON
        return;
    }

    server.send(
        400,
        "application/json",
        "{\"success\":false,\"message\":\"Action inconnue\"}"
    ); // requête failed renvoyée par JSON
}

// Setup

void setup() // config et démarrage des composants et routes
{
    server.on("/api/command", HTTP_POST, handleCommand); // config de la route de commande
    server.on("/api/command", HTTP_OPTIONS, handleOptions); // config de la route d'options (envoi des headers cors)
    server.on("/health", HTTP_GET, handleHealth); // config de la route pour vérifier si l'appareil est OK
    
    Serial.begin(115200); // Définir la vitesse de l'ESP

    connectWifi(); // connexion au wifi

    if (MDNS.begin(MDNS_HOSTNAME)) // si appareil enregistré sur wifi
    {
        Serial.print("Adresse locale : http://");
        Serial.print(MDNS_HOSTNAME);
        Serial.println(".local");
    }
    else // Si appareil pas enregistré sur le wifi
    {
        Serial.println("Erreur de démarrage mDNS");
    }

    lightSensor.begin(); // démarrer le capteur de luminosité
    arm.begin(); // démarrer le bras motorisé
    distance.begin(); // démarrer le capteur de distance
    led.begin(); // démarrer les lampes

    server.begin(); // démarrer le serveur

    Serial.println();
    Serial.println("Systeme pret");
    Serial.println("Serveur HTTP demarre");
}


// Loop

void loop() // boucle de fonctionnement
{
    server.handleClient(); // check si requête envoyée
    MDNS.update(); // vérifie l'accès à l'appareil

    int lightValue = lightSensor.read(); // récupérer la luminosité
    float distanceValue = distance.read(); // récupérer la distance

    if (distanceValue != -1 && distanceValue < LIMIT_DISTANCE_DANGER) // S'il y a un obstacle et qu'il est à une distance trop proche
    {

        if (arm.isOpen()) // Si le bras est déployé
        {
            led.red(); // allumage de la led rouge

            arm.close(); // repli du bras

            Serial.println("Repli du bras car obstacle");
        }
        manualMode = false; // mode automatique
    }
    else if (!manualMode) // si on est en mode automatique
    {

        if (lightValue > LIMIT_LIGHT && arm.isClosed()) // Si le bras n'est pas déployé et qu'il y a assez de lumière
        {

            led.green(); // allumage de la led verte

            arm.open(); // déplier le bras

            Serial.println("Déploiement du bras car lumière");
        }


        else if (lightValue < LIMIT_DARK && arm.isOpen()) // Si le bras est déployé et qu'il n'y a plus de lumière
        {
            led.red(); // allumage de la led en rouge

            arm.close(); // replier le bras

            Serial.println("Repli du bras car obscurité");
        }
    }

    bool panelOpen = arm.isOpen(); // récupérer si le bras est ouvert ou non

    apiClient.sendMeasurement(lightValue, distanceValue, panelOpen); // envoi des valeurs à l'API pour écriture en BDD

    // Display

    server.handleClient(); // check si requête envoyée
    for (int i = 0; i < 60; ++i) // réalise 60 fois cette requête
    {
        server.handleClient(); // check si requête envoyée
        MDNS.update(); // vérifier l'accès à l'appareil
        delay(25);
    }

    Serial.print("Lumiere : ");
    Serial.print(lightValue);

    Serial.print(" | Bras : ");
    Serial.print(arm.getAngle());

    Serial.print(" | Distance : ");
    Serial.print(distanceValue);
    Serial.println();

    led.unlit(); // éteindre la led
}