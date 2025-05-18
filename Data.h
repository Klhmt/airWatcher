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
    Sensor * getSensorById(string id);

    vector<Sensor*> getSensors();
    

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
    vector<AirCleaner*> airCleaners;
    vector<Sensor*> sensors;
    unordered_map<string, Sensor*> sensorsMap;
    vector<Measurement*> measurements;
    vector<PrivateOwner*> privateOwners;
    vector<Provider*> providers; 
    string baseFolderPath; // chemin vers le dossier
};

//-------------------------------- Autres définitions dépendantes de <Data>

#endif // Data_H

