#ifndef PROJETRSP_API_CLIENT_H
#define PROJETRSP_API_CLIENT_H
#include <Arduino.h>

// Prépare et envoie les mesures de l'ESP à l'API HTTP du projet.
class ApiClient {
public:
    // Conserve l'URL et les identifiants nécessaires aux appels API.
    ApiClient(
        const char* apiUrl,
        const char* username,
        const char* password
    );

    // Réserve l'interface d'authentification prévue pour l'API.
    bool login();
    // Envoie luminosité, distance et état du panneau sous forme JSON.
    void sendMeasurement(int light, float distance, bool panelOpen);

private:
    const char* _apiUrl;
    const char* _username;
    const char* _password;

    String _token;
};

#endif // PROJETRSP_API_CLIENT_H