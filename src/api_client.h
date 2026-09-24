#ifndef PROJETRSP_API_CLIENT_H // si le fichier n'est pas déjà inclus
#define PROJETRSP_API_CLIENT_H // inclure le fichier
#include <Arduino.h>

class ApiClient {
public:
    ApiClient( // constructeur
        const char* apiUrl,
        const char* username,
        const char* password
    );

    bool login(); // fonction de login
    void sendMeasurement(int light, float distance, bool panelOpen); // fonction d'envoi des mesures

private: // variables internes
    const char* _apiUrl;
    const char* _username;
    const char* _password;

    String _token; // token JWT
};

#endif // PROJETRSP_API_CLIENT_H