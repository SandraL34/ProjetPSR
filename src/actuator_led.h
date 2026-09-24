#ifndef PROJETRSP_ACTUATOR_LED_H
#define PROJETRSP_ACTUATOR_LED_H

// Pilote les LED rouge et verte qui indiquent l'état du panneau.
class ActuatorLed {
    public:
        // Associe chaque couleur à sa broche de sortie.
        ActuatorLed(int pinRed, int pinGreen);

        // Configure les sorties et éteint les LED.
        void begin();

        // Affiche un état d'alerte ou de repli.
        void red() const;
        // Affiche un état normal ou de déploiement.
        void green() const;
        // Éteint les deux indicateurs.
        void unlit() const;

    private:
        const int _pinRed;
        const int _pinGreen;
};

#endif // PROJETRSP_ACTUATOR_LED_H