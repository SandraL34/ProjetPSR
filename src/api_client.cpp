#include "api_client.h"

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

ApiClient::ApiClient(const char* apiUrl, const char* username, const char* password)
    : _apiUrl(apiUrl),
    _username(username),
    _password(password)
{
}

void ApiClient::sendMeasurement(int light, float distance, bool panelOpen)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Wi-Fi non connecté, mesure non envoyée.");
        return;
    }

    WiFiClient client;
    HTTPClient http;

    http.begin(client, _apiUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{";
    json += "\"light\":" + String(light);
    json += ",\"distance\":" + String(distance, 2);
    json += ",\"panel_open\":" + String(panelOpen ? "true" : "false");
    json += "}";

    Serial.print("JSON envoyé : ");
    Serial.println(json);

    int httpCode = http.POST(json);

    Serial.print("Code HTTP : ");
    Serial.println(httpCode);

    if (httpCode > 0)
    {
        String response = http.getString();

        Serial.print("Réponse API : ");
        Serial.println(response);
    }
    else
    {
        Serial.print("Erreur HTTP : ");
        Serial.println(http.errorToString(httpCode));
    }

    http.end();
}