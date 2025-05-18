/*************************************************************************
                           Data  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Data> (fichier Data.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <unordered_map>

//------------------------------------------------------ Include personnel
#include "Data.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Data::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode



bool Data::loadPrivateOwnersAndSensors(const string& userPath, const string& sensorPath)
{
    unordered_map<string, PrivateOwner*> mapUser;        // map de nom vers pointeur
    unordered_map<string, PrivateOwner*> sensorToOwner;  // map de capteur vers propriétaire

    // 1. Lire User.csv
    ifstream userFile(userPath);
    string line;

    if (!userFile)
    {
        cerr << "Erreur : impossible d'ouvrir " << userPath << endl;
        return false;
    }

    while (getline(userFile, line))
    {
        istringstream ss(line);
        string user, sensor;
        ss >> user >> sensor;

        // Créer le propriétaire s'il n'existe pas déjà
        if (mapUser.find(user) == mapUser.end())
        {
            PrivateOwner* owner = new PrivateOwner(user, 0);
            mapUser[user] = owner;
            privateOwners.push_back(owner);
        }

        // Associer le capteur à ce propriétaire
        sensorToOwner[sensor] = mapUser[user];
    }

    userFile.close();

    // 2. Lire Sensor.csv
    ifstream sensorFile(sensorPath);

    if (!sensorFile)
    {
        cerr << "Erreur : impossible d'ouvrir " << sensorPath << endl;
        return false;
    }

    while (getline(sensorFile, line))
    {
        istringstream ss(line);
        string id;
        float lat, lon;

        ss >> id >> lat >> lon;

        // Récupérer propriétaire ou nullptr
        PrivateOwner* owner = nullptr;
        if (sensorToOwner.find(id) != sensorToOwner.end())
        {
            owner = sensorToOwner[id];
        }

        // Créer le capteur (non défectueux par défaut)
        Sensor* s = new Sensor(id, lat, lon, false, owner);
        sensors.push_back(s); // stocker l'objet dans le vector
        sensorsMap[id] = s; // A tester
    }

    sensorFile.close();
    return true;
}

bool Data::loadProviderAndAirWatcher(const string& providerFilePath, const string& cleanerFilePath)
{
    unordered_map<string, Provider*> providerMap;
    unordered_map<string, string> cleanerToProviderID;

    // 1. Lire providerFilePath pour associer les cleaners aux providers
    ifstream providerFile(providerFilePath);
    if (!providerFile)
    {
        cerr << "Erreur : impossible d'ouvrir " << providerFilePath << endl;
        return false;
    }

    string line;
    while (getline(providerFile, line))
    {
        istringstream ss(line);
        string providerID, cleanerID;

        if (!getline(ss, providerID, ';') || !getline(ss, cleanerID, ';'))
        {
            cerr << "Format incorrect dans providerFile : " << line << endl;
            continue;
        }

        // Créer le Provider s'il n'existe pas déjà
        if (providerMap.find(providerID) == providerMap.end())
        {
            Provider* p = new Provider(providerID);
            providerMap[providerID] = p;
            providers.push_back(p);
        }

        // Stocker temporairement l'association Cleaner → Provider
        cleanerToProviderID[cleanerID] = providerID;
    }

    providerFile.close();

    // 2. Lire cleanerFilePath et créer les AirCleaners
    ifstream cleanerFile(cleanerFilePath);
    if (!cleanerFile)
    {
        cerr << "Erreur : impossible d'ouvrir " << cleanerFilePath << endl;
        return false;
    }

    while (getline(cleanerFile, line))
    {
        istringstream ss(line);
        string id;
        string latStr, lonStr;
        string y1, m1, d1, h1, min1, s1;
        string y2, m2, d2, h2, min2, s2;

        if (!getline(ss, id, ';') ||
            !getline(ss, latStr, ';') ||
            !getline(ss, lonStr, ';') ||
            !getline(ss, y1, '-') || !getline(ss, m1, '-') || !getline(ss, d1, ';') ||
            !getline(ss, h1, ';') || !getline(ss, min1, ';') || !getline(ss, s1, ';') ||
            !getline(ss, y2, '-') || !getline(ss, m2, '-') || !getline(ss, d2, ';') ||
            !getline(ss, h2, ';') || !getline(ss, min2, ';') || !getline(ss, s2, ';'))
        {
            cerr << "Format incorrect dans cleanerFile : " << line << endl;
            continue;
        }

        float lat = stof(latStr);
        float lon = stof(lonStr);

        Date start(stoi(y1), stoi(m1), stoi(d1), stoi(h1), stoi(min1), stoi(s1));
        Date stop(stoi(y2), stoi(m2), stoi(d2), stoi(h2), stoi(min2), stoi(s2));

        // Récupérer le Provider associé
        Provider* p = nullptr;
        if (cleanerToProviderID.find(id) != cleanerToProviderID.end())
        {
            string providerID = cleanerToProviderID[id];
            p = providerMap[providerID];
        }

        // Créer le AirCleaner
        AirCleaner* cleaner = new AirCleaner(id, lon, lat, start, stop, p);
        airCleaners.push_back(cleaner);
    }

    cleanerFile.close();
    return true;
}


vector<Sensor*> Data::getSensors()
{
    return sensors;
}


//------------------------------------------------- Surcharge d'opérateurs
//Data & Data::operator = ( const Data & unData )
// Algorithme :
//
//{
//} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Data::Data ( const Data & unData )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Data>" << endl;
#endif
} //----- Fin de Data (constructeur de copie)


Data::Data ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Data>" << endl;
#endif
} //----- Fin de Data


Data::Data ( string path )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Data>" << endl;
#endif
    baseFolderPath = path;
} //----- Fin de Data


Data::~Data ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Data>" << endl;
#endif
    // Libération mémoire pour éviter que Valgrind nous saute à la figure !!!
    for (size_t i = 0; i < privateOwners.size(); ++i)
    {
        delete privateOwners[i];
    }

    // Libérer les Sensors
    for (size_t i = 0; i < sensors.size(); ++i)
    {
        delete sensors[i];
    }

    // Libérer les Measurements
    for (size_t i = 0; i < measurements.size(); ++i)
    {
        delete measurements[i];
    }

    // Libérer les AirCleaners
    for (size_t i = 0; i < airCleaners.size(); ++i)
    {
        delete airCleaners[i];
    }

    // Libérer les Providers
    for (size_t i = 0; i < providers.size(); ++i) {
        delete providers[i];
    }
    providers.clear();

} //----- Fin de ~Data


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

