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
            privateOwners.push_back(*owner);
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
        sensors.push_back(*s); // stocker une copie dans le vecteur
    }

    sensorFile.close();
    return true;
}

bool Data::loadProviderAndAirWatcher(const string& providerFilePath, const string& cleanerFilePath)
{
    unordered_map<string, string> cleanerToProvider;
    unordered_map<string, Provider*> providers;

    ifstream providerFile(providerFilePath);
    ifstream cleanerFile(cleanerFilePath);

    if (!providerFile.is_open() || !cleanerFile.is_open())
    {
        cerr << "Erreur d'ouverture des fichiers." << endl;
        return false;
    }

    // Lire les associations Provider <-> Cleaner
    string line;
    while (getline(providerFile, line))
    {
        istringstream iss(line);
        string providerID, cleanerID;
        if (!(iss >> providerID >> cleanerID)) continue;
        cleanerToProvider[cleanerID] = providerID;
    }

    // Lire les informations de chaque cleaner
    while (getline(cleanerFile, line))
    {
        istringstream iss(line);
        string cleanerID, startDateStr, endDateStr;
        float lat, lon;
        int sh, sm, ss, eh, em, es;

        if (!(iss >> cleanerID >> lat >> lon >> startDateStr >> sh >> sm >> ss >> endDateStr >> eh >> em >> es))
        {
            cerr << "Erreur de parsing ligne : " << line << endl;
            continue;
        }

        // Conversion de la date de début
        int sy, smon, sd;
        sscanf(startDateStr.c_str(), "%d-%d-%d", &sy, &smon, &sd);
        Date startDate(sy, smon, sd, sh, sm, ss);

        // Conversion de la date de fin
        int ey, emon, ed;
        sscanf(endDateStr.c_str(), "%d-%d-%d", &ey, &emon, &ed);
        Date endDate(ey, emon, ed, eh, em, es);

        // Chercher ou créer le Provider
        Provider* provider = nullptr;
        auto it = cleanerToProvider.find(cleanerID);
        if (it != cleanerToProvider.end())
        {
            string providerID = it->second;
            if (providers.find(providerID) == providers.end())
            {
                provider = new Provider(providerID);
                providers[providerID] = provider;
                // Optionnel : ajouter à ta collection interne
            }
            else
            {
                provider = providers[providerID];
            }
        }

        // Créer l'AirCleaner
        AirCleaner* cleaner = new AirCleaner(cleanerID, lon, lat, startDate, endDate, provider);

        // Optionnel : ajouter le cleaner à ta collection interne
        airCleaners.push_back(*cleaner);
        
    }

    providerFile.close();
    cleanerFile.close();
    return true;
}


vector<Sensor> Data::getSensors()
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
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Data>" << endl;
#endif
} //----- Fin de ~Data


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

