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

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Data>
//
//
//------------------------------------------------------------------------

class Data 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //


//------------------------------------------------- Surcharge d'opérateurs
    //Data & operator = ( const Data & unData );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    Data ( const Data & unData );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Data ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Data ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    bool loadAttribute(String chemin);
    bool loadPrivateOwner(String chemin);
    bool loadProvider(String chemin);
    bool loadSensor(String chemin);
    bool loadAirCleaner(String chemin);
    bool loadMeasurement(String chemin, )

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Data>

#endif // Data_H

