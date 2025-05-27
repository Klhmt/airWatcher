/*************************************************************************
                           Sensor  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Sensor.h) ----------------
#if ! defined ( Sensor_H )
#define Sensor_H

//---------------------------------------------------------- Includes
#include <iostream>
#include <string>
#include "PrivateOwner.h"


using namespace std;


//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
//
//  Modélise un capteur
//------------------------------------------------------------------------

class Sensor
{
    //----------------------------------------------------------------- PUBLIC
    public :

    //-------------------------------------------- Constructeurs 
    Sensor(); 

    Sensor(string id, float lat, float lon, bool defectueux, PrivateOwner* prop);

    //--------------------------------- Destructeur
    ~Sensor();

    //--------------------------------- Getters
    string getSensorId() const;

    float getLatitude() const;

    float getLongitude() const;

    bool getEstDefectueux() const;

    PrivateOwner* getProprietaire() const;

    //--------------------------------- Setters
    void setSensorId(string id);

    void setLatitude(float lat);

    void setLongitude(float lon);

    void setEstDefectueux(bool defectueux);

    void setProprietaire(PrivateOwner* prop);

    // Méthodes 

    void desactiverCapteur();
    // Mode d'emploi : marque le capteur comme défectueux. Permet de ne plus utiliser les mesures de ce capteurs

    //------------------------------------------------------------------ PRIVE


    private :

    string sensorId;
    float latitude;
    float longitude;
    bool estDefectueux;
    PrivateOwner* proprietaire;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // Sensor_H