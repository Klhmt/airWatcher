/*************************************************************************
                           AirCleaner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <AirCleaner> (fichier AirCleaner.h) ----------------
#if ! defined ( AIRCLEANER_H )
#define AIRCLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include "Provider.h"
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types
//------------------------------------------------------------------------
// Rôle de la classe <AirCleaner>
//
//
//------------------------------------------------------------------------

class AirCleaner 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    string getAirCleanerId();

    float getLongtitude();

    float getLatitude();


//------------------------------------------------- Surcharge d'opérateurs
    AirCleaner & operator = ( const AirCleaner & unAirCleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    AirCleaner (string id, float lon, float lat, Provider* user);
    //Constructeur normal
    
    AirCleaner ( const AirCleaner & unAirCleaner );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    AirCleaner (  );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AirCleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    
//----------------------------------------------------- Attributs protégés
    string cleanerId;
    float latitude;
    float longtitude;
    // type de Date ?? start et end
    Provider* proprietaire;
};

//-------------------------------- Autres définitions dépendantes de <AirCleaner>

#endif // AIRCLEANER_H

