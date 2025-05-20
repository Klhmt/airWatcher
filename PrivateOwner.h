/*************************************************************************
                           PrivateOwner  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <PrivateOwner> (fichier PrivateOwner.h) ----------------

#if ! defined ( PRIVATEOWNER_H )
#define PRIVATEOWNER_H

//---------------------------------------------------------- Includes
#include <iostream>
#include <string>

using namespace std;

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <PrivateOwner>
//
//  Modélise un particulier qui possède un ou des capteurs
//------------------------------------------------------------------------


class PrivateOwner
{   
    //----------------------------------------------------------------- PUBLIC
    public:

    //-------------------------------------------- Constructeurs - destructeur
    PrivateOwner(string name, int pts);
    // Constructeur utilisé dans l'app

    PrivateOwner();
    // Constructeur par défaut

    ~PrivateOwner();

    //------------------------------------------------------------------ PRIVE

    private:
        string userName;
        int points;
};

//-------------------------------- Autres définitions dépendantes de <PrivateOwner>

#endif // PRIVATEOWNER_H 