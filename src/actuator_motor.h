#ifndef PROJETRSP_MOTOR_H // si le fichier n'est pas déjà inclus
#define PROJETRSP_MOTOR_H // inclure le fichier


class ActuatorMotor { // constructeur
    public:
        ActuatorMotor(int pin);

        void begin();  // fonction de démarrage
        void move(int angle); // fonction de mouvement du bras
        void open(); // fonction de déploiement du bras
        void close(); // fonction de repli du bras

        int getAngle() const; // fonction de récupération de la valeur de l'angle du bras

        bool isOpen() const; // fonction de récupération de la valeur du bras si ouvert
        bool isClosed() const; // fonction de récupération de la valeur du bras si fermé

    private: // variables internes
        const int _pin;
        int _angle;

        const int _angleOpen = 100;
        const int _angleClosed = 0;
};


#endif
