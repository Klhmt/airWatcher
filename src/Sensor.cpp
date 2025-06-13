//---------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ------------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeur par défaut
Sensor::Sensor()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur par défaut de <Sensor>" << endl;
    #endif
} //----- Fin du constructeur par défaut


//-------------------------------------------- Constructeur avec paramètres
Sensor::Sensor(string id, float lat, float lon, bool defectueux, PrivateOwner* prop)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur avec paramètres de <Sensor>" << endl;
    #endif

    sensorId = id;
    latitude = lat;
    longitude = lon;
    estDefectueux = defectueux;
    proprietaire = prop;
} //----- Fin du constructeur avec paramètres


//-------------------------------------------- Destructeur
Sensor::~Sensor()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
    #endif
} //----- Fin du destructeur


//-------------------------------------------- Getters
string Sensor::getSensorId() const
{
    return sensorId;
}


float Sensor::getLatitude() const
{
    return latitude;
}

float Sensor::getLongitude() const
{
    return longitude;
}

bool Sensor::getEstDefectueux() const
{
    return estDefectueux;
}

PrivateOwner* Sensor::getProprietaire() const
{
    return proprietaire;
}


//-------------------------------------------- Setters
void Sensor::setSensorId(string id)
{
    sensorId = id;
}

void Sensor::setLatitude(float lat)
{
    latitude = lat;
}

void Sensor::setLongitude(float lon)
{
    longitude = lon;
}

void Sensor::setEstDefectueux(bool defectueux)
{
    estDefectueux = defectueux;
}

void Sensor::setProprietaire(PrivateOwner* prop)
{
    proprietaire = prop;
}


//-------------------------------------------- Méthodes

void Sensor::desactiverCapteur()
{
    #ifdef MAP
    cout << "Appel à la méthode desactiverCapteur de <Sensor>" << endl;
    #endif

    // Désactiver le capteur
    estDefectueux = true;
    cout << "Le capteur " << sensorId << " a été désactivé." << endl;

} //----- Fin de la méthode desactiverCapteur