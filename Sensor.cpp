#include "Sensor.h"

// Constructeur par défaut
Sensor::Sensor()
{
 
}

// Constructeur avec paramètres
Sensor::Sensor(string id, float lat, float lon, bool defectueux, PrivateOwner* prop)
{
    sensorId = id;
    latitude = lat;
    longitude = lon;
    estDefectueux = defectueux;
    proprietaire = prop;
}

// Destructeur
Sensor::~Sensor()
{
    delete proprietaire;
    proprietaire = nullptr;
}

// Getters
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


// Setters
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

void Sensor::setProprietaire(PrivateOwner* owner)
{
    proprietaire = owner;
}


// Autres méthodes
void Sensor::desactiverCapteur()
{
    estDefectueux = true;
    cout << "Le capteur " << sensorId << " a été désactivé." << endl;
}