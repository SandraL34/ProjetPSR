#ifndef PROJETRSP_API_CLIENT_H
#define PROJETRSP_API_CLIENT_H
#include <Arduino.h>

class ApiClient {
public:
    ApiClient(
        const char* apiUrl,
        const char* username,
        const char* password
    );

    bool login();
    void sendMeasurement(int light, float distance, bool panelOpen);

private:
    const char* _apiUrl;
    const char* _username;
    const char* _password;

    String _token;
};

#endif // PROJETRSP_API_CLIENT_H