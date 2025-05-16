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

#include <string>
#include <unordered_map>
#include <vector>
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
    int determinerFiabiliteCapteur(string sensorId);

    int calculerQualiterAir(float lat, float lon, float radius, Date start, Date end);

    vector<Measurement> observerImpactAir();

    unordered_map<Sensor,float> indentifierCapteursSimilaires(string sensorId);

    bool bannirCapteur(string sensorId);

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

    virtual ~Service ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    
//----------------------------------------------------- Attributs protégés

private:
    //Methodes privees
    vector<Sensor> capteursProches(float lat, float lon, float radius);

    int calculerQualiterParCapteur(Sensor sensor, Date start, Date stop);

};

//-------------------------------- Autres définitions dépendantes de <Service>

#endif // SERVICE_H

