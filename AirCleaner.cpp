/*************************************************************************
                           AirCleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <AirCleaner> (fichier AirCleaner.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "AirCleaner.h"

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques
// type AirCleaner::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
string AirCleaner::getAirCleanerId()
{
    return cleanerId;
}

float AirCleaner::getLongtitude()
{
    return longtitude;
}

float AirCleaner::getLatitude()
{
    return latitude;
}


//------------------------------------------------- Surcharge d'opérateurs
AirCleaner & AirCleaner::operator = ( const AirCleaner & unAirCleaner )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
AirCleaner::AirCleaner ( string id, float lon, float lat, Date start, Date stop, Provider* user)
{
    cleanerId = id;
    longtitude = lon;
    latitude = lat;
    start = start;
    stop = stop;
    proprietaire = user;
}


AirCleaner::AirCleaner ( const AirCleaner & unAirCleaner )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AirCleaner>" << endl;
#endif
} //----- Fin de AirCleaner (constructeur de copie)


AirCleaner::AirCleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AirCleaner>" << endl;
#endif
} //----- Fin de AirCleaner


AirCleaner::~AirCleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AirCleaner>" << endl;
#endif
} //----- Fin de ~AirCleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées