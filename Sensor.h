#include <iostream>
#include <string>
#include "PrivateOwner.h"

using namespace std;



class Sensor
{
    public :

    // Constructeurs
    Sensor(); 
    Sensor(string id, float lat, float lon, bool defectueux, PrivateOwner* owner);

    // Destructeur
    ~Sensor();

    // Getters 
    string getSensorId() const;

    float getLatitude() const;

    float getLongitude() const;

    bool getEstDefectueux() const;

    PrivateOwner* getProprietaire() const;

    // Setters
    void setSensorId(string id);

    void setLatitude(float lat);

    void setLongitude(float lon);

    void setEstDefectueux(bool defectueux);

    void setProprietaire(PrivateOwner* owner);

    // Autres méthodes 
    void desactiverCapteur();


    private :
    // Attributs privés
    string sensorId;
    float latitude;
    float longitude;
    bool estDefectueux;
    PrivateOwner* proprietaire;
};