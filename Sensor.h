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
//
//------------------------------------------------------------------------

class Sensor
{
    //----------------------------------------------------------------- PUBLIC
    public :

    //-------------------------------------------- Constructeurs 
    Sensor(); 
    Sensor(string id, float lat, float lon, bool defectueux, PrivateOwner* owner);

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

    void setProprietaire(PrivateOwner* owner);

    // Autres méthodes 
    void desactiverCapteur();

    //------------------------------------------------------------------ PRIVE


    private :
    // Attributs privés
    string sensorId;
    float latitude;
    float longitude;
    bool estDefectueux;
    PrivateOwner* proprietaire;
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // Sensor_H