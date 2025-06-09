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

// Alias du type de structure pour stocker les mesures
// Clé: ID du capteur
// Valeur: map des dates vers vecteurs de mesures
typedef unordered_map<string, map<Date, vector<Measurement*>>> dataStructure;

/*
  Classe Data
  -----------
  Lit des fichiers CSV, crée des objets métiers et les organise
  dans des conteneurs STL pour un traitement ultérieur.
 */
class Data 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    /*
      Charge les propriétaires privés et leurs capteurs.
      @param userPath    Chemin vers le fichier users.csv (format: userID;sensorID;)
      @param sensorPath  Chemin vers le fichier sensors.csv (format: sensorID;lat;lon;)
      @return true si le chargement réussit, false sinon
     */
    bool loadPrivateOwnersAndSensors(const string& userPath, const string& sensorPath); 

    /*
      Charge les fournisseurs et leurs AirCleaners.
      @param providerFilePath  Chemin vers providers.csv (format: providerID;cleanerID;)
      @param cleanerFilePath   Chemin vers cleaners.csv (format: id;lat;lon;start;stop;)
      @return true si le chargement réussit, false sinon
     */
    bool loadProviderAndAirWatcher(const string& providerFilePath, const string& cleanerFilePath);


    /*
      Charge les mesures environnementales.
      Doit être appelé après loadPrivateOwnersAndSensors pour initialiser sensorsMap.
      @param measurementFilePath  Chemin vers measurements.csv
      @return true si le chargement réussit, false sinon
     */
    bool loadMeasurements(const string& measurementFilePath);

    /// Affiche la structure de données des mesures (debug)
    void printDataStructure();

    /// Affiche la map des capteurs (debug)
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
    
    Data ( );
    Data ( const Data & unData );
    /*
      Construit à partir d'un fichier listant les chemins des datasets:
      1. providers.csv
      2. cleaners.csv
      3. users.csv
      4. sensors.csv
      5. measurements.csv
     */
    Data (const string& fileGroupePath );

    /* Destructeur de la classe Data.
     Ce destructeur se charge de libérer tous les objets alloués dynamiquement
     (PrivateOwner, Sensor, AirCleaner, Provider, Measurement)
     qui étaient stockés dans les vecteurs et maps membres de la classe Data.
     Il libère la mémoire allouée dynamiquement, puis assigne nullptr aux pointeurs
     pour éviter les pointeurs pendants.
     On fait cela pour que Valgrind ne nous remonte pas d’erreurs :) !!
    */
    virtual ~Data ( );
    

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    vector<Sensor*> sensors;    /// Tous les capteurs chargés
    vector<PrivateOwner*> privateOwners;    /// Tous les propriétaires privés
    vector<Provider*> providers;    /// Tous les fournisseurs
    vector<AirCleaner*> airCleaners;    /// Tous les AirCleaners
    unordered_map<string, Sensor*> sensorsMap;    /// Accès rapide capteur par ID
    dataStructure measurements;     /// Mesures par capteur et date
    string baseFolderPath;     /// chemin vers le dossier
};

//-------------------------------- Autres définitions dépendantes de <Data>

#endif // Data_H

