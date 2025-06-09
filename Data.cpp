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
#include <algorithm>



//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Data::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


/*
 * Supprime les espaces, retours chariot et saut de ligne aux deux bouts
 */
string trim(const string& str) {
    string result = str;
    result.erase(result.find_last_not_of(" \r\n") + 1);  
    result.erase(0, result.find_first_not_of(" \r\n")); 
    return result;
}

bool Data::loadPrivateOwnersAndSensors(const string& userPath, const string& sensorPath)
{   // Map temporaire capteur->propriétaire
    unordered_map<string, PrivateOwner*> assocSensorOwner; 
    // Assure l'unicité des PrivateOwner créés
    unordered_map<string, PrivateOwner*> uniquePrivateOwners; 

    ifstream file(userPath);
    if (!file.is_open()) {
        cout << "Erreur : impossible d'ouvrir le fichier " << userPath << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string userID, sensorID;

        // Lecture des 3 champs séparés par des ;
        if (!getline(ss, userID, ';')) continue;
        if (!getline(ss, sensorID, ';')) continue;

        
        // Crée un nouveau PrivateOwner si besoin
        PrivateOwner * user = nullptr;
        if (uniquePrivateOwners.find(userID) == uniquePrivateOwners.end())
        {
            user = new PrivateOwner(userID, 0);
            privateOwners.push_back(user);
            uniquePrivateOwners[userID] = user;
        }
        else
        {
            user = uniquePrivateOwners[userID];
        }
        // Associe le capteur au propriétaire
        assocSensorOwner[sensorID] = user;
        
    }
    
    file.close();

    // Lecture des informations GPS des capteurs
    ifstream file2(sensorPath);
    if (!file2.is_open()) {
        cout << "Erreur : impossible d'ouvrir le fichier " << sensorPath << endl;
        return false;
    }

    while (getline(file2, line)) {
        stringstream ss(line);
        string sensorID, latitude, longitude;

        // Lecture des 3 champs séparés par des ;
        if (!getline(ss, sensorID, ';')) continue;
        if (!getline(ss, latitude, ';')) continue;
        if (!getline(ss, longitude, ';')) continue;

        float latitudeConvertie = 0;
        float longitudeConvertie = 0;

        // Conversion en float
        latitudeConvertie = stof(latitude);
        longitudeConvertie = stof(longitude);

        // Cherche propriétaire associé (ou nullptr)
        PrivateOwner * owner = nullptr;
        if (assocSensorOwner.find(sensorID) != assocSensorOwner.end())
        {
            owner = assocSensorOwner[sensorID];
        }

        // Création et stockage du Sensor
        Sensor * sensor = new Sensor(sensorID, latitudeConvertie, longitudeConvertie, false, owner);
        sensors.push_back(sensor);
        sensorsMap[sensorID] = sensor;

    }

    file2.close();
    return true;
}

bool Data::loadProviderAndAirWatcher(const string& providerFilePath, const string& cleanerFilePath)
{
    unordered_map<string, Provider*> providerMap;
    unordered_map<string, string> cleanerToProviderID;

    // --- 1. Lecture des associations provider-cleaner ---
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

    // --- 2. Lecture des AirCleaners ---
    ifstream cleanerFile(cleanerFilePath);
    if (!cleanerFile)
    {
        cerr << "Erreur : impossible d'ouvrir " << cleanerFilePath << endl;
        return false;
    }

    while (getline(cleanerFile, line))
    {
        istringstream ss(line);
        string id, latStr, lonStr, startStr, stopStr;

        if (!getline(ss, id, ';') ||
            !getline(ss, latStr, ';') ||
            !getline(ss, lonStr, ';') ||
            !getline(ss, startStr, ';') ||
            !getline(ss, stopStr, ';'))
        {
            cerr << "Format incorrect dans cleanerFile : " << line << endl;
            continue;
        }
        // Conversion coordonnées
        float lat = stof(latStr);
        float lon = stof(lonStr);

        // Découper startStr et stopStr manuellement
        int y1, m1, d1, h1, min1, s1;
        int y2, m2, d2, h2, min2, s2;

        sscanf(startStr.c_str(), "%d-%d-%d %d:%d:%d", &y1, &m1, &d1, &h1, &min1, &s1);
        sscanf(stopStr.c_str(),  "%d-%d-%d %d:%d:%d", &y2, &m2, &d2, &h2, &min2, &s2);

        Date start(y1, m1, d1, h1, min1, s1);
        Date stop(y2, m2, d2, h2, min2, s2);

        // Récupérer le Provider associé
        Provider* p = nullptr;
        if (cleanerToProviderID.find(id) != cleanerToProviderID.end())
        {
            string providerID = cleanerToProviderID[id];
            p = providerMap[providerID];
        }

        // Créer et stocker le AirCleaner
        AirCleaner* cleaner = new AirCleaner(id, lon, lat, start, stop, p);
        airCleaners.push_back(cleaner);
    }


    cleanerFile.close();
    return true;
}


void Data::printDataStructure()
{   // Parcourt toutes les mesures pour affichage
    for (const auto& sensorEntry : measurements)
    {
        const string& sensorID = sensorEntry.first;
        const map<Date, vector<Measurement*>>& measurementsByDate = sensorEntry.second;

        cout << "Sensor ID: " << sensorID << endl;

        for (const auto& dateEntry : measurementsByDate)
        {
            const Date& date = dateEntry.first;
            const vector<Measurement*>& measurements = dateEntry.second;

            cout << "  Date: " << date << endl; // ou cout << date << si operator<< existe

            for (const Measurement* m : measurements)
            {
                // À adapter selon ce que Measurement contient
                cout << "    ";
                cout << "Type: " << m->getAttribute() << ", ";
                cout << "Value: " << m->getValue() << endl;
            }
        }

        cout << "----------------------------------" << endl;
    }
}


void Data::printSensorsMap()
{   // Affiche chaque clé/valeur de sensorsMap
    for (const auto& pair : sensorsMap) {
        cout << "Key: " << pair.first << ", Value: " << (*(pair.second)).getSensorId() << endl;
    }
}

bool Data::loadMeasurements(const string& measurementFilePath) {
    ifstream file(measurementFilePath);
    if (!file.is_open()) {
        cout << "Erreur : impossible d'ouvrir le fichier " << measurementFilePath << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string datetimeStr, sensorID, pollutant, valueStr;

        // Lecture des 5 champs séparés par des ;
        if (!getline(ss, datetimeStr, ';')) continue;
        if (!getline(ss, sensorID, ';')) continue;
        if (!getline(ss, pollutant, ';')) continue;
        if (!getline(ss, valueStr, ';')) continue;

        // Parse datetime "YYYY-MM-DD HH:MM:SS"
        int year, month, day, hour, minute, second;
        if (sscanf(datetimeStr.c_str(), "%d-%d-%d %d:%d:%d",
                   &year, &month, &day, &hour, &minute, &second) != 6) {
            cout << "Format de date/heure invalide : " << datetimeStr << endl;
            continue;
        }

        float value = stof(valueStr);

        // Vérification de l'existence du capteur
        auto it = sensorsMap.find(sensorID);
        if (it == sensorsMap.end()) {
            cout << "Capteur non trouvé : " << sensorID << endl;
            continue;
        }
        Sensor* sensor = it->second;

        // Création des objets
        Date date(year, month, day, hour, minute, second);
        Measurement* measurement = new Measurement(pollutant, value, date, sensor);

        // Ajout dans la dataStructure
        measurements[sensorID][date].push_back(measurement);
    }

    file.close();
    return true;
}

// Getters

vector<Sensor*> Data::getSensors()
{
    return sensors;
}

Sensor* Data::getSensorById(std::string id) {
    std::unordered_map<std::string, Sensor*>::iterator it = sensorsMap.find(id);
    if (it != sensorsMap.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

vector<PrivateOwner*> Data::getPrivateOwner()
{
    return privateOwners;
}

vector<Provider*> Data::getProvider()
{
    return providers;
}

vector<AirCleaner*> Data::getAirCleaner()
{
    return airCleaners;
}

unordered_map<string, Sensor*> Data::getSensorsMap()
{
    return sensorsMap;
}

dataStructure Data::getMeasurements()
{
    return measurements;
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


Data::Data (const string& fileGroupePath )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Data>" << endl;
#endif
    ifstream file(fileGroupePath);
    if (!file.is_open()) {
        cout << "Erreur : impossible d'ouvrir le fichier " << fileGroupePath << endl;
        return;
    }
    // file groupe contient les paths suivi ces odres : 
    // 1. ./dataset/providers.csv
    // 2. ./dataset/cleaners.csv
    // 3. ./dataset/users.csv
    // 4. ./dataset/sensors.csv
    // 5. ./dataset/mesurements.csv ou mesurements_tests.csv ....

    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    if (lines.size() >= 5) {
        this->loadProviderAndAirWatcher(trim(lines[0]), trim(lines[1]));
        this->loadPrivateOwnersAndSensors(trim(lines[2]), trim(lines[3]));
        this->loadMeasurements(trim(lines[4]));
    } else {
        cout << "Erreur : le fichier doit contenir 5 paths." << endl;
    }

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
        privateOwners[i] = nullptr;
    }

    // Libérer les Sensors
    for (size_t i = 0; i < sensors.size(); ++i)
    {
        delete sensors[i];
        sensors[i] = nullptr;
    }

    // Libérer les AirCleaners
    for (size_t i = 0; i < airCleaners.size(); ++i)
    {
        delete airCleaners[i];
        airCleaners[i] = nullptr;
    }

    // Libérer les Providers
    for (size_t i = 0; i < providers.size(); ++i) {
        delete providers[i];
        providers[i] = nullptr;
    }
    providers.clear();

    // Libérer les Measurement
    for (pair<const string, map<Date, vector<Measurement*>>>& sensorPair : measurements) {
        for (pair<const Date, vector<Measurement*>>& datePair : sensorPair.second) {
            for (Measurement* m : datePair.second) {
                delete m;
                m = nullptr;
            }
        }
    }

} //----- Fin de ~Data


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

