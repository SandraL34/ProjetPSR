#ifndef PROJETRSP_MOTOR_H
#define PROJETRSP_MOTOR_H


// Contrôle le servomoteur qui déploie ou replie le panneau.
class ActuatorMotor {
    public:
        // Associe l'actionneur à sa broche de commande.
        ActuatorMotor(int pin);

        // Configure le PWM et place le bras en position fermée.
        void begin();
        // Déplace le bras vers un angle compris entre 0 et 180 degrés.
        void move(int angle);
        // Utilise l'angle prédéfini d'ouverture.
        void open();
        // Utilise l'angle prédéfini de fermeture.
        void close();

        // Retourne le dernier angle commandé au servomoteur.
        int getAngle() const;

        // Indique si le dernier angle commandé correspond à l'ouverture.
        bool isOpen() const;
        // Indique si le dernier angle commandé correspond à la fermeture.
        bool isClosed() const;

    private:
        const int _pin;
        int _angle;

        const int _angleOpen = 100;
        const int _angleClosed = 0;
};


#endif
