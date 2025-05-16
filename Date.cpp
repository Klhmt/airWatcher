/*************************************************************************
                           Date -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Date> (fichier Date.cpp) ------------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Date.h"

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeur par défaut
Date::Date()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur par défaut de <Date>" << endl;
    #endif
} //----- Fin du constructeur par défaut


//-------------------------------------------- Constructeur avec paramètres
Date::Date(int annee, int mois, int jour, int heure, int minute, int seconde)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur avec paramètres de <Date>" << endl;
    #endif

    this->annee = annee;
    this->mois = mois;
    this->jour = jour;
    this->heure = heure;
    this->minute = minute;
    this->seconde = seconde;

} //----- Fin du constructeur avec paramètres


//-------------------------------------------- Destructeur
Date::~Date()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au destructeur de <Date>" << endl;
    #endif

} //----- Fin du destructeur


//-------------------------------------------- Getters
int Date::getAnnee() const
// Algorithme :
// 
{
    return annee;
} //----- Fin getter année

int Date::getMois() const
// Algorithme : 
// 
{
    return mois;
} //----- Fin getter mois

int Date::getJour() const
// Algorithme :
// 
{
    return jour;
} //----- Fin getter jour

int Date::getHeure() const
// Algorithme :
//
{
    return heure;
} //----- Fin getter heure

int Date::getMinute() const
// Algorithme :
//
{
    return minute;
} //----- Fin getter minute

int Date::getSeconde() const
// Algorithme :
// 
{
    return seconde;
} //----- Fin getter seconde

//-------------------------------------------- Setters
void Date::setAnnee(int annee)
// Algorithme :
// 
{
    this->annee = annee;
} //----- Fin setter année

void Date::setMois(int mois)
// Algorithme :
// 
{
    this->mois = mois;
} //----- Fin setter mois

void Date::setJour(int jour)
// Algorithme :
// 
{
    this->jour = jour;
} //----- Fin setter jour

void Date::setHeure(int heure)
// Algorithme :
// 
{
    this->heure = heure;
} //----- Fin setter heure

void Date::setMinute(int minute)
// Algorithme :
// 
{
    this->minute = minute;
} //----- Fin setter minute

void Date::setSeconde(int seconde)
// Algorithme :
// 
{
    this->seconde = seconde;
} //----- Fin setter seconde

//-------------------------------------------- Autres méthodes

// Surcharge de l'opérateur << pour l'affichage de la date
ostream& operator<<(ostream& os, const Date& date)
// Algorithme : 
// 
{
    os << date.getAnnee() << "-" << date.getMois() << "-" << date.getJour() << " "
       << date.getHeure() << ":" << date.getMinute() << ":" << date.getSeconde();
    return os;
} //----- Fin de l'opérateur <<

