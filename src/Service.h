//---------- Interface de la classe <Service> (fichier Service.h) ----------------
#if ! defined ( SERVICE_H )
#define SERVICE_H

//--------------------------------------------------- Interfaces utilisées
#include "Measurement.h"
#include "Sensor.h"
#include "Date.h"
#include "Data.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Service>
//
//  Concentre tous les traitements "métiers" de l'application AirWatcher
//------------------------------------------------------------------------

class Service 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques


    // Converts a pollutant concentration value to the corresponding ATMO index level.
    // Parameters:
    // - pollutant: name of the pollutant ("O3", "SO2", "NO2", "PM10")
    // - value: measured concentration of the pollutant
    // Returns:
    // - The ATMO index (1 to 10) corresponding to the concentration
    // - Returns -1 if the pollutant is unknown or the value is out of defined bounds
    // Thresholds are based on:
    // https://fr.wikipedia.org/wiki/Indice_de_qualit%C3%A9_de_l%27air
    int convertirEnIndiceATMO(const string& pollutant, float value);

    // Determines the reliability of a sensor over a given time period.
    // Compares the sensor’s quality to that of its neighbors within a specified radius.
    // Parameters:
    //   sensorId - ID of the sensor to evaluate
    //   radius - radius within which to consider neighboring sensors
    //   ecartMax - maximum allowed deviation percentage for quality comparison
    //   debut - start date of the evaluation period
    //   fin - end date of the evaluation period
    // Returns 0 on error or no data, 1 if reliable, and 2 if not reliable.
    int determinerFiabiliteCapteur(string sensorId, float radius, float ecartMax, Date debut, Date fin);

    // Calculates the average air quality index (ATMO) around a geographic point
    // based on sensors within a specified radius and time range.
    // Parameters:
    // - lat, lon: coordinates of the reference point (in degrees)
    // - radius: search radius in kilometers
    // - start, end: date range for measurement consideration
    // Returns:
    // - Average ATMO index (rounded int) of valid sensors in the area
    // - Returns -1 if no sensors found or no valid data in the period
    int calculerQualiterAir(float lat, float lon, float radius, Date start, Date end);

    // Checks if a sensor with the given ID exists in the dataset.
    // Parameters:
    // - sensorId: ID of the sensor to check
    // Returns:
    // - true if the sensor exists, false otherwise
    bool verifierExistenceCapteur(string sensorId);

    // Returns a vector of measurements containing information about air purifiers (aircleaners)
    // along with statistics computed from their data (e.g., average, min, max).
    // Used to evaluate the impact of aircleaners on air quality.
    // NOT IMPLEMENTED
    vector<Measurement> observerImpactAir();

    // Returns an unordered map containing pointers to sensors similar to the given sensor,
    // each associated with a similarity score (float). The sensors are ranked in descending order
    // based on similarity using the ATMO index calculated over a defined period.
    // NOT IMPLEMENTED
    unordered_map<Sensor*,float> indentifierCapteursSimilaires(string sensorId);

    // Mark the sensor as unreliable. All the measurements of this sensor
    // won't be used at all for the future ATMO calculations.
    // Parameter:
    // - sensorId: ID of the sensor to ban
    void bannirCapteur(string sensorId);

    int consulterRecompense(string userName);

    // Calculates the ATMO index for a given sensor over a specified time range.
    // Parameters:
    // - sensor: pointer to the Sensor object
    // - start, stop: date range for which to compute ATMO
    // Returns:
    // - The ATMO index based on the highest pollutant level measured. ATMO index is calculated using convertirEnIndiceATMO method.
    // - Returns -1 if the sensor has no data or no measurements in the given period
    int calculerQualiterParCapteur(Sensor* sensor, Date start, Date stop);

    // Returns a vector of pointers to Sensor objects located within a given radius (in kilometers)
    // from the specified latitude and longitude.
    // Parameters:
    // - lat, lon: reference coordinates (in degrees)
    // - radius: search radius (in kilometers)
    // Uses the Haversine-based distance() function to compute distances.
    vector<Sensor*> capteursProches(float lat, float lon, float radius);

    // Calculates the distance in kilometers between two geographic coordinates
    // using the Haversine formula.
    // Parameters:
    // - latitude1, longitude1: coordinates of the first point (in degrees)
    // - latitude2, longitude2: coordinates of the second point (in degrees)
    // Returns:
    // - Distance in kilometers
    double distance(float latitude1, float longitude1, float latitude2, float longitude2);

//------------------------------------------------- Surcharge d'opérateurs
    Service & operator = ( const Service & unService );


//-------------------------------------------- Constructeurs - destructeur
    
    Service ( const Service & unService );

    Service (  );

    Service (const string& filePath);

    virtual ~Service ( );


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

private:
    // Methodes privees

    // Attributs prives
    Data data;


};

//-------------------------------- Autres définitions dépendantes de <Service>

#endif // SERVICE_H

