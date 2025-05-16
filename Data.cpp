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



void Data::loadPrivateOwnersAndSensors(const string& userPath, const string& sensorPath)
{
    unordered_map<string, PrivateOwner*> mapUser;        // map de nom vers pointeur
    unordered_map<string, PrivateOwner*> sensorToOwner;  // map de capteur vers propriétaire

    // 1. Lire User.csv
    ifstream userFile(userPath);
    string line;

    if (!userFile)
    {
        cerr << "Erreur : impossible d'ouvrir " << userPath << endl;
        return;
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
        return;
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

