#include "api_client.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

ApiClient::ApiClient(const char* apiUrl, const char* username, const char* password) // constructeur de l'API
    : _apiUrl(apiUrl),
    _username(username),
    _password(password)
{
}

void ApiClient::sendMeasurement(int light, float distance, bool panelOpen) // envoi des mesures recueillies
{
    if (WiFi.status() != WL_CONNECTED) // si wifi non connecté
    {
        Serial.println("Wi-Fi non connecté, mesure non envoyée.");
        return;
    }

    WiFiClient client; // création de la gestion TCP/IP
    HTTPClient http; // création de la gestion HTTP

    http.begin(client, _apiUrl); // démarrage de la connexion vers l'API
    http.addHeader("Content-Type", "application/json"); // Ajout header pour lecture JSON

    String json = "{"; // Création du JSON
    json += "\"light\":" + String(light);
    json += ",\"distance\":" + String(distance, 2);
    json += ",\"panel_open\":" + String(panelOpen ? "true" : "false");
    json += "}";

    Serial.print("JSON envoyé : ");
    Serial.println(json);

    int httpCode = http.POST(json); // envoi du JSON

    Serial.print("Code HTTP : ");
    Serial.println(httpCode);

    if (httpCode > 0) // si connexion réussie
    {
        String response = http.getString();

        Serial.print("Réponse API : ");
        Serial.println(response);
    }
    else // si connexion échouée
    {
        Serial.print("Erreur HTTP : ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end(); // stoppe le wifi
}