/*************************************************************************
                           Service  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Service> (fichier Service.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Service.h"
#include <cmath>
//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//une function distance:
int distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}


//----------------------------------------------------- Méthodes publiques
// type Service::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


int Service::determinerFiabiliteCapteur(string sensorId, float radius, float ecartMax)
// Algorithme : on prend les capteurs voisins dans le radius, on calcule leur qualite moyen 
//              et compare avec la qualite de ce capteur avec un ecart max
//              renvoie 0 si erreue (sensorId non valide, pas de capteurs proches ou pas assez de donnees), 1 si fiable et 2 sinon
//{
//} //----- Fin de Méthode
{
    Sensor* s = data.getCapteurParId(sensorId);
    if (s == nullptr) return 0;

    vector<Sensor> capteursProches = this->capteursProches()

}


int Service::calculerQualiterAir(float lat, float lon, float radius, Date start, Date end)
{

}


vector<Measurement> Service::observerImpactAir()
{

}


unordered_map<Sensor,float> Service::indentifierCapteursSimilaires(string sensorId)
{

}


void Service::bannirCapteur(string sensorId)
{
    data.getCapteurParId(sensorId)->desactiverCapteur();
}


int Service::consulterRecompense(string userName)
{

}


//------------------------------------------------- Surcharge d'opérateurs
Service & Service::operator = ( const Service & unAirCleaner )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

Service::Service ( const Service & unAirCleaner )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Service>" << endl;
#endif
} //----- Fin de Service (constructeur de copie)


Service::Service ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Service>" << endl;
#endif
} //----- Fin de Service


Service::~Service ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Service>" << endl;
#endif
} //----- Fin de ~Service


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

vector<Sensor> Service::capteursProches(float lat, float lon, float radius)
{
    vector<Sensor> listCapteurProche;
    vector<Sensor> allCapteur = data.getSensors();

    for (Sensor& capteur : allCapteur)   /// Sensor& ou juste Sensor ????
    {
        if (distance(lat,lon,capteur.getLatitude(),capteur.getLongitude()) < radius)
        {
            listCapteurProche.push_back(capteur);
        } 
    }
    return listCapteurProche;
}

int Service::calculerQualiterParCapteur(Sensor sensor, Date start, Date stop)
{

}