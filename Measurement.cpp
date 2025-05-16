/*************************************************************************
                           Measurement -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Measurement> (fichier Measurement.cpp) ------------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Measurement.h"

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeur par défaut
Measurement::Measurement()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur par défaut de <Measurement>" << endl;
    #endif
} //----- Fin du constructeur par défaut


//-------------------------------------------- Constructeur avec paramètres
Measurement::Measurement(string id, float val, Date* date, Sensor* sensor, vector<float> measurements)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur avec paramètres de <Measurement>" << endl;
    #endif

    attributeId = id;
    value = val;
    this->date = date;
    this->sensor = sensor;
    this->measurements = measurements;

} //----- Fin du constructeur avec paramètres


//-------------------------------------------- Destructeur
Measurement::~Measurement()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au destructeur de <Measurement>" << endl;
    #endif

    if (date != nullptr)
    {
        delete date;
        date = nullptr;
    }

    if (sensor != nullptr)
    {
        delete sensor;
        sensor = nullptr;
    }
} //----- Fin du destructeur


//-------------------------------------------- Getters
string Measurement::getAttributeId() const
// Algorithme :
// 
{
    return attributeId;
} //----- Fin de getAttributeId

float Measurement::getValue() const
// Algorithme :
// 
{
    return value;
} //----- Fin de getValue

Date* Measurement::getDate() const
// Algorithme :
// 
{
    return date;
} //----- Fin de getDate

Sensor* Measurement::getSensor() const
// Algorithme :
// 
{
    return sensor;
} //----- Fin de getSensor

vector<float> Measurement::getMeasurements() const
// Algorithme :
// 
{
    return measurements;
} //----- Fin de getMeasurements


//-------------------------------------------- Setters
void Measurement::setAttributeId(string id)
// Algorithme :
// 
{
    attributeId = id;
} //----- Fin de setAttributeId

void Measurement::setValue(float val)
// Algorithme :
// 
{
    value = val;
} //----- Fin de setValue

void Measurement::setDate(Date* date)
// Algorithme :
// 
{
    if (this->date != nullptr)
    {
        delete this->date;
    }
    this->date = date;
} //----- Fin de setDate

void Measurement::setSensor(Sensor* sensor)
// Algorithme :
// 
{
    if (this->sensor != nullptr)
    {
        delete this->sensor;
    }
    this->sensor = sensor;
} //----- Fin de setSensor

void Measurement::setMeasurements(vector<float> measurements)
// Algorithme :
// 
{
    this->measurements = measurements;
} //----- Fin de setMeasurements

//-------------------------------------------- Autres méthodes

