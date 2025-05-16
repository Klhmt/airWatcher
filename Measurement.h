/*************************************************************************
                           Measurement  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Measurement> (fichier Measurement.h) ----------------
#if ! defined ( Measurement_H )
#define Measurement_H

//---------------------------------------------------------- Includes
#include <iostream>
#include <string>
#include "Sensor.h"

using namespace std;


//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Measurement>
//
//
//------------------------------------------------------------------------

class Measurement
{
    //----------------------------------------------------------------- PUBLIC
    public :

    //-------------------------------------------- Constructeurs 
    Measurement(); 
    Measurement(string id, float value, string date);

    //--------------------------------- Destructeur
    ~Measurement();


    private :
    // Attributs privés
    // ajouter la date
    Sensor* sensor;
    string attributeId;
    float value;
};

//-------------------------------- Autres définitions dépendantes de <Measurement>

#endif // MEASUREMENT_H