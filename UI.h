/*************************************************************************
                           UI  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <UI> (fichier UI.h) ----------------
#if ! defined ( UI_H )
#define UI_H

//---------------------------------------------------------- Includes
#include <iostream>
#include "Service.h"

using namespace std;


//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <UI>
//
//
//------------------------------------------------------------------------

class UI
{
    //----------------------------------------------------------------- PUBLIC
    public :

    //-------------------------------------------- Constructeur avec paramètres
    UI(Service& s);

    //--------------------------------- Destructeur
    ~UI();

    // Autres méthodes 
    bool authentification();    
    void application();

    //------------------------------------------------------------------ PRIVE

    private :
    Service &service; // Instance de la classe Service 
    // Attributs privés
   
};

//-------------------------------- Autres définitions dépendantes de <Sensor>

#endif // UI_H