#include "Sensor.h"

Sensor::Sensor(string id, float lat, float lon, bool defectueux, PrivateOwner* prop)
{
    sensorId = id;
    latitude = lat;
    longitude = lon;
    estDefectueux = defectueux;
    proprietaire = prop;
}

Sensor::~Sensor()
{
    delete proprietaire;
    proprietaire = nullptr;
}

void Sensor::desactiverCapteur()
{
    estDefectueux = true;
    cout << "Le capteur " << sensorId << " a été désactivé." << endl;
}