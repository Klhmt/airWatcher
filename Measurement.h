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
#include <vector>

#include "Sensor.h"
#include "Date.h"

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

    Measurement(string attribut, float val, Date date, Sensor* sensor);
    //--------------------------------- Destructeur
    ~Measurement();

    //--------------------------------- Getters
    string getAttribute() const;
    float getValue() const;
    Date getDate() const;
    Sensor* getSensor() const;


    private :
    // Attributs privés
    string attribute;
    float value;
    Date date;
    Sensor* sensor;    
};

//-------------------------------- Autres définitions dépendantes de <Measurement>

#endif // MEASUREMENT_H