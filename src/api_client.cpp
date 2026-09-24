#include "api_client.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

ApiClient::ApiClient(const char* apiUrl, const char* username, const char* password)
    : _apiUrl(apiUrl),
    _username(username),
    _password(password)
{
    // Conserve les paramètres d'authentification et l'adresse de l'API pour les envois futurs.
}

void ApiClient::sendMeasurement(int light, float distance, bool panelOpen)
{
    // Une mesure ne peut être envoyée que si l'ESP est connecté au Wi-Fi.
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Wi-Fi non connecté, mesure non envoyée.");
        return;
    }

    WiFiClient client;
    HTTPClient http;

    // Ouvre une connexion HTTP et indique que le corps sera encodé en JSON.
    http.begin(client, _apiUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    // Assemble les trois valeurs de capteurs dans le format attendu par l'API Symfony.
    json += "\"light\":" + String(light);
    json += ",\"distance\":" + String(distance, 2);
    json += ",\"panel_open\":" + String(panelOpen ? "true" : "false");
    json += "}";

    Serial.print("JSON envoyé : ");
    Serial.println(json);

    // Envoie la mesure et conserve le code HTTP pour diagnostiquer la réponse du serveur.
    int httpCode = http.POST(json);

    Serial.print("Code HTTP : ");
    Serial.println(httpCode);

    if (httpCode > 0)
    {
        // Affiche la réponse du serveur lorsque la requête HTTP a bien abouti.
        String response = http.getString();

        Serial.print("Réponse API : ");
        Serial.println(response);
    }
    else
    {
        // Affiche le détail fourni par la bibliothèque lorsque la connexion a échoué.
        Serial.print("Erreur HTTP : ");
        Serial.println(http.errorToString(httpCode));
    }

    // Libère les ressources réseau utilisées par la requête.
    http.end();
}