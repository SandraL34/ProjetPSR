#ifndef PROJETRSP_ACTUATOR_LED_H // si le fichier n'est pas déjà inclus
#define PROJETRSP_ACTUATOR_LED_H // inclure le fichier

class ActuatorLed { // constructeur
    public:
        ActuatorLed(int pinRed, int pinGreen);

        void begin(); // fonction de démarrage

        void red() const; // fonction d'allumage de la led en rouge
        void green() const; // fonction d'allumage de la led en vert
        void unlit() const; // fonction d'extinction des leds

    private: // variables internes
        const int _pinRed;
        const int _pinGreen;
};

#endif // PROJETRSP_ACTUATOR_LED_H