/*************************************************************************
                           Date  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Sensor> (fichier Date.h) ----------------
#if ! defined ( Date_H )
#define Date_H

//---------------------------------------------------------- Includes
#include <iostream>
#include <string>
#include <regex>


using namespace std;


//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Date>
//
//
//------------------------------------------------------------------------

class Date
{
    //----------------------------------------------------------------- PUBLIC
    public :
    
    //------------------------------------------Surcharges operateurs
    friend bool operator<(const Date& d1, const Date& d2);
    friend bool operator>(const Date& d1, const Date& d2);
    friend bool operator==(const Date& d1, const Date& d2);
    friend bool operator>=(const Date& d1, const Date& d2);
    friend bool operator<=(const Date& d1, const Date& d2);
    
    
    //-------------------------------------------- Constructeurs 
    Date(); 

    Date(int annee, int mois, int jour, int heure, int minute, int seconde);

    Date(const Date & unDate);

    //--------------------------------- Destructeur
    ~Date();

    //--------------------------------- Getters
    int getAnnee() const;
    int getMois() const;
    int getJour() const;
    int getHeure() const;
    int getMinute() const;
    int getSeconde() const;

    //--------------------------------- Setters
    void setAnnee(int annee);
    void setMois(int mois);
    void setJour(int jour);
    void setHeure(int heure);
    void setMinute(int minute);
    void setSeconde(int seconde);

    // Autres méthodes 
   bool lireDate(int &jour, int &mois, int &annee);
   bool lireHeure(int &heure, int &minute, int &seconde);

    // Surcharge de l'opérateur << pour l'affichage de la date
    friend ostream& operator<<(ostream& os, const Date& date);

    //------------------------------------------------------------------ PRIVE


    private :
    // Attributs privés
    int annee;
    int mois;
    int jour;
    int heure;
    int minute;
    int seconde;

  
};

//-------------------------------- Autres définitions dépendantes de <Date>

#endif // Date_H