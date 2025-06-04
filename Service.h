/*************************************************************************
                           Service  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Service> (fichier Service.h) ----------------
#if ! defined ( SERVICE_H )
#define SERVICE_H

//--------------------------------------------------- Interfaces utilisées
#include "Measurement.h"
#include "Sensor.h"
#include "Date.h"
#include "Data.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Service>
//
//
//------------------------------------------------------------------------

class Service 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    int convertirEnIndiceATMO(const string& pollutant, float value);

    int determinerFiabiliteCapteur(string sensorId, float radius, float ecartMax, Date debut, Date fin);

    int calculerQualiterAir(float lat, float lon, float radius, Date start, Date end);

    bool verifierExistenceCapteur(string sensorId);

    vector<Measurement> observerImpactAir();

    unordered_map<Sensor*,float> indentifierCapteursSimilaires(string sensorId);

    void bannirCapteur(string sensorId);

    int consulterRecompense(string userName);

//------------------------------------------------- Surcharge d'opérateurs
    Service & operator = ( const Service & unService );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    
    Service ( const Service & unService );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Service (  );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Service (const string& filePath);

    virtual ~Service ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    int calculerQualiterParCapteur(Sensor* sensor, Date start, Date stop);
    vector<Sensor*> capteursProches(float lat, float lon, float radius);
    double distance(float latitude1, float longitude1, float latitude2, float longitude2);


//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    
    
//----------------------------------------------------- Attributs protégés

private:
    // Methodes privees


    // Attributs prives
    Data data;


};

//-------------------------------- Autres définitions dépendantes de <Service>

#endif // SERVICE_H

