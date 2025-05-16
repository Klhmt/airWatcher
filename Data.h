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
#include "Sensor.h"
#include "Provider.h"
#include "PrivateOwner.h"
#include "AirCleaner.h"
#include <vector>
//#include "AirCleaner.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

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

    vector<Sensor> getSensors();
    

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
    vector<AirCleaner> airCleaners;
    vector<Sensor> sensors;
    vector<PrivateOwner> privateOwners;
    string baseFolderPath; // chemin vers le dossier
};

//-------------------------------- Autres définitions dépendantes de <Data>

#endif // Data_H

