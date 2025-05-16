#include <iostream>
#include <string>
#include "PrivateOwner.h"

using namespace std;



class Sensor
{
    public :

    Sensor(string id, float lat, float lon, bool defectueux, PrivateOwner* owner);

    ~Sensor();

    void desactiverCapteur();


    private :

    string sensorId;
    float latitude;
    float longitude;
    bool estDefectueux;
    PrivateOwner* proprietaire;
};