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
    Measurement(string id, float val, Date* date, Sensor* sensor, vector<float> measurements);
    //--------------------------------- Destructeur
    ~Measurement();

    //--------------------------------- Getters
    string getAttributeId() const;
    float getValue() const;
    Date* getDate() const;
    Sensor* getSensor() const;
    vector<float> getMeasurements() const;

    //--------------------------------- Setters
    void setAttributeId(string id);
    void setValue(float val);
    void setDate(Date* date);
    void setSensor(Sensor* sensor);
    void setMeasurements(vector<float> measurements);


    private :
    // Attributs privés
    string attributeId;
    float value;
    Date* date;
    Sensor* sensor;
    vector<float> measurements;
    
};

//-------------------------------- Autres définitions dépendantes de <Measurement>

#endif // MEASUREMENT_H