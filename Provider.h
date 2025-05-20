/*************************************************************************
                           Provider  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Provider> (fichier Provider.h) ----------------
#if ! defined ( PROVIDER_H )
#define PROVIDER_H

//--------------------------------------------------- Interfaces utilisées
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Provider>
//
//  Modélise un provider d'AirCleaner
//------------------------------------------------------------------------

class Provider 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

//------------------------------------------------- Surcharge d'opérateurs
    Provider & operator = ( const Provider & unProvider );

//-------------------------------------------- Constructeurs - destructeur
    Provider ( const string name);
    // Constructeur utilisé dans l'app
    
    Provider ( const Provider & unProvider );
    // Constructeur de copie

    Provider (  );
    // Constructeur par défaut

    virtual ~Provider ( );
    // Destructeur

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    
//----------------------------------------------------- Attributs protégés
    string providerName;
};

//-------------------------------- Autres définitions dépendantes de <Provider>

#endif // PROVIDER_H

