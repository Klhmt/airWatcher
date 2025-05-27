/*************************************************************************
                           Data  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Data> (fichier Data.h) ----------------
#if ! defined ( DATA_H )
#define DATA_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#include "Date.h"
#include "Sensor.h"
#include "Provider.h"
#include "PrivateOwner.h"
#include "AirCleaner.h"
#include "Measurement.h"
#include "AirCleaner.h"

using namespace std;

class Measurement;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

typedef unordered_map<string, map<Date, vector<Measurement*>>> dataStructure;

//------------------------------------------------------------------------
// Rôle de la classe <Data>
//
//  Read CSV files, creates domain objet and put them into STL containers
//------------------------------------------------------------------------

class Data 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    // This function loads private owner and sensor data from two specified files.
    // It populates the 'privateOwners', 'sensors', and 'sensorsMap' members of the Data class.
    //
    // Parameters:
    //   userPath: The file path to the private owner (user) data. Format: userID;sensorID;
    //   sensorPath: The file path to the sensor data. Format: sensorID;latitude;longitude;
    //
    // Returns:
    //   true if both files are successfully opened and processed; false otherwise.
    bool loadPrivateOwnersAndSensors(const string& userPath, const string& sensorPath); 

    // This function loads provider and air cleaner data from two specified files.
    // It populates the 'providers' (vector<Provider*>) and 'airCleaners' (vector<AirCleaner*>)
    // members of the Data class.
    //
    // Parameters:
    //   providerFilePath: Path to the provider association file. Format: providerID;cleanerID;
    //   cleanerFilePath: Path to the air cleaner details file. Format: id;lat;lon;startStr;stopStr;
    //
    // Returns:
    //   true if both files are successfully opened and processed; false otherwise
    bool loadProviderAndAirWatcher(const string& providerFilePath, const string& cleanerFilePath);


    // This function loads environmental measurement data from a specified file.
    // It populates the 'measurements' member of the Data class, which is assumed
    // to be a complex data structure (e.g., unordered_map<string, unordered_map<Date, vector<Measurement*>>>).
    //
    //  CONTRACT : loadPrivateOwnersAndSensors has to be called BEFORE to populate sensorsMap & sensors attributes
    //
    // Parameters:
    //   measurementFilePath: The file path to the measurement data.
    //                        Format per line: datetime;sensorID;pollutant;value;
    //                        datetime format: YYYY-MM-DD HH:MM:SS
    //
    // Returns:
    //   true if the file is successfully opened and processed; false otherwise.
    bool loadMeasurements(const string& measurementFilePath);

    // Display measurements attribute on std::cout. For debugging purposes only
    void printDataStructure();

    // Display sensorsMap attribute on std::cout. For debugging purposes only
    void printSensorsMap();

    //-------- Getters ---------

    Sensor * getSensorById(string id);

    vector<Sensor*> getSensors();

    vector<PrivateOwner*> getPrivateOwner();

    vector<Provider*> getProvider();

    vector<AirCleaner*> getAirCleaner();

    unordered_map<string, Sensor*> getSensorsMap();

    dataStructure getMeasurements();
    

//-------------------------------------------- Constructeurs - destructeur
    Data ( const Data & unData );

    Data ( );

    Data (const string& fileGroupePath );

    // Destructor for the Data class.
    // This destructor is responsible for deallocating all dynamically allocated
    // objects (PrivateOwner, Sensor, AirCleaner, Provider, Measurement)
    // that were stored in the Data class's member vectors and maps.
    // It frees the dynamically allocated memory, then sets the pointer to nullptr to avoid dangling pointers.
    // We do that because otherwise Valgrind is gonna scream at us :) !!!
    virtual ~Data ( );
    

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<Sensor*> sensors;
    vector<PrivateOwner*> privateOwners;
    vector<Provider*> providers;  
    vector<AirCleaner*> airCleaners;
    unordered_map<string, Sensor*> sensorsMap;
    dataStructure measurements;
    string baseFolderPath; // chemin vers le dossier
};

//-------------------------------- Autres définitions dépendantes de <Data>

#endif // Data_H

