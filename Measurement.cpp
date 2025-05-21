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
Measurement::Measurement(string attribut, float val, Date date, Sensor* sensor)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur avec paramètres de <Measurement>" << endl;
    #endif

    attribute = attribut;
    value = val;
    this->date = date;
    this->sensor = sensor;

} //----- Fin du constructeur avec paramètres


//-------------------------------------------- Destructeur
Measurement::~Measurement()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au destructeur de <Measurement>" << endl;
    #endif
} //----- Fin du destructeur


//-------------------------------------------- Getters
string Measurement::getAttribute() const
// Algorithme :
// 
{
    return attribute;
} //----- Fin de getAttributeId

float Measurement::getValue() const
// Algorithme :
// 
{
    return value;
} //----- Fin de getValue

Date Measurement::getDate() const
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

//-------------------------------------------- Autres méthodes

