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
//
//------------------------------------------------------------------------

class Data 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    bool loadPrivateOwnersAndSensors(const string& userPath, const string& sensorPath);

    bool loadProviderAndAirWatcher(const string& providerFilePath, const string& cleanerFilePath);

    bool loadMeasurements(const string& measurementFilePath);
    // Contrat :
    //      Doit être appelée APRES avoir appelé loadPrivateOwnersAndSensors, car l'attribut sensorsMap doit être peuplé

    Sensor * getSensorById(string id);

    vector<Sensor*> getSensors();

    vector<PrivateOwner*> getPrivateOwner();

    vector<Provider*> getProvider();

    vector<AirCleaner*> getAirCleaner();

    unordered_map<string, Sensor*> getSensorsMap();

    dataStructure getMeasurements();
    

//-------------------------------------------- Constructeurs - destructeur
    Data ( const Data & unData );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Data ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Data (string path);

    virtual ~Data ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

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

