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

Date::Date(const Date &unData)
{
    annee = unData.annee;
    mois = unData.mois;
    jour = unData.jour;
    heure = unData.heure;
    minute = unData.minute;
    seconde = unData.seconde;
}

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
ostream &operator<<(ostream &os, const Date &date)
// Algorithme :
//
{
    os << date.getAnnee() << "-" << date.getMois() << "-" << date.getJour() << " "
       << date.getHeure() << ":" << date.getMinute() << ":" << date.getSeconde();
    return os;
} //----- Fin de l'opérateur <<

// Surcharge de l'opérateur < pour pouvoir utiliser Date dans une map
bool operator<(const Date &d1, const Date &d2)
{
    if (d1.annee != d2.annee)
        return d1.annee < d2.annee;
    if (d1.mois != d2.mois)
        return d1.mois < d2.mois;
    if (d1.jour != d2.jour)
        return d1.jour < d2.jour;
    if (d1.heure != d2.heure)
        return d1.heure < d2.heure;
    if (d1.minute != d2.minute)
        return d1.minute < d2.minute;
    return d1.seconde < d2.seconde;
}
bool operator>(const Date& d1, const Date& d2)
{
    if (d1.annee != d2.annee) return d1.annee < d2.annee;
    if (d1.mois != d2.mois) return d1.mois < d2.mois;
    if (d1.jour != d2.jour) return d1.jour < d2.jour;
    if (d1.heure != d2.heure) return d1.heure < d2.heure;
    if (d1.minute != d2.minute) return d1.minute < d2.minute;
    return d1.seconde < d2.seconde;
}

bool operator==(const Date& d1, const Date& d2)
{
    return d1.annee == d2.annee &&
           d1.mois == d2.mois &&
           d1.jour == d2.jour &&
           d1.heure == d2.heure &&
           d1.minute == d2.minute &&
           d1.seconde == d2.seconde;
}

bool operator>(const Date& d1, const Date& d2)
{
    return d2 < d1;
}

bool operator<=(const Date& d1, const Date& d2)
{
    return !(d1 > d2);
}

bool operator>=(const Date& d1, const Date& d2)
{
    return !(d1 < d2);
}

bool Date::lireDate(int &jour, int &mois, int &annee)
// Algorithme :
//
{
    string date;

    // Format de date attendu : jj/mm/yyyy
    regex formatStrict(R"(^\s*(\d{2})/(\d{2})/(\d{4})\s*$)");
    smatch match;

    while (true)
    {
        
        getline(cin >> ws, date);

        if (!regex_match(date, match, formatStrict))
        {
            cout << "Erreur, veuillez entrer une date valide : ";
            continue;
        }

        // Extraction des valeurs de jour, mois et année
        jour = stoi(match[1]);
        mois = stoi(match[2]);
        annee = stoi(match[3]);

        // Vérification de la validité de la date
        if (mois < 1 || mois > 12 || jour < 1)
        {
            cout << "Erreur, veuillez entrer une date valide : ";
            continue;
        }

        // Nombre de jours maximum par mois
        int joursParMois[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        // Si le nombre de jours est supérieur au nombre de jours maximum du mois
        if (jour > joursParMois[mois - 1])
        {
            cout << "Erreur, veuillez entrer une date valide : ";
            continue;
        }
        break;
    }

    return true;

} //----- Fin de lireDate


bool Date::lireHeure(int &heure, int &minute, int &seconde)
// Algorithme :
//
{
    string heureStr;
    regex formatStrict(R"(^\s*(\d{2}):(\d{2})\s*$)");
    smatch match;

    while (true)
    {
        getline(cin >> ws, heureStr);

        if (!regex_match(heureStr, match, formatStrict))
        {
            cout << "Erreur, veuillez entrer une heure valide : ";
            continue;
        }

        heure = stoi(match[1]);
        minute = stoi(match[2]);
        seconde = 0; // valeur à 0 par défaut

        if (heure < 0 || heure > 23)
        {
            cout << "Erreur, veuillez entrer une heure valide : ";
            continue;
        }

        if (minute < 0 || minute > 59)
        {
            cout << "Erreur, veuillez entrer une heure valide : ";
            continue;
        }

        break; 
    }

    return true;
}  //----- Fin de lireHeure


