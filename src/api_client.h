#ifndef PROJETRSP_API_CLIENT_H
#define PROJETRSP_API_CLIENT_H


class ApiClient {
    public:
        ApiClient(const char* apiUrl);

        void sendMeasurement(int light, float distance, bool panelOpen);

    private:
        const char* _apiUrl;
};


#endif //PROJETRSP_API_CLIENT_H
