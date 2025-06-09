/*************************************************************************
                           UI -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <UI> (fichier UI.cpp) ------------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>

//------------------------------------------------------ Include personnel
#include "UI.h"
#include "Date.h"

using namespace std;

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeur avec paramètres

UI::UI(Service &s) : service(s)
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur de <UI> avec Service" << endl;
    #endif
} //----- Fin du constructeur avec paramètres


//-------------------------------------------- Destructeur
UI::~UI()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au destructeur de <UI>" << endl;
    #endif

} //----- Fin du destructeur
  

bool UI::authentification()
// Algorithme :
// 
{
    bool resultat = false;
    int choix = 0;
    cout << "-------------------------------------------------" << endl;
    cout << "Bienvenue, tout d'abord veuillez vous authentifier : " << endl;
    cout << "1. Agence Gouvernementale" << endl;
    cout << "2. Fournisseur" << endl;
    cout << "3. Particulier" << endl;
    cout << "4. Quitter l'application" << endl;
    cout << "Veuillez entrer votre choix : ";
    cin >> choix;

    switch (choix)
    {
        case 1:
            cout << "Vous etes une Agence Gouvernementale" << endl;
            // Appeler la méthode pour l'agence gouvernementale
            resultat = true;
            break;

        case 2:
            cout << "Vous etes un Fournisseur" << endl;
            // Appeler la méthode pour le fournisseur
            resultat = true;
            break;

        case 3:
            cout << "Vous etes un Particulier" << endl;
            // Appeler la méthode pour le particulier
            resultat = true;
            break;

        case 4:
            cout << "Merci d'avoir utilise AirWatcher, au revoir !!!" << endl;
            break;

        default:
            cout << "Choix invalide, veuillez reessayer." << endl;
            authentification();
            break;
    }

    return resultat;
} //----- Fin de la méthode authentification

//-------------------------------------------- Autres méthodes


void UI::application()
// Algorithme :
// 
{
    bool continuer = true;

    while (continuer)
    {
        Date date, dateDebut, dateFin;
        int jour, mois, annee;
        int heure, minute, seconde;
        float latitude, longitude, rayon;
        int choix = 0;
        cout << "-------------------------------------------------" << endl;
        cout << "Bienvenue dans l'application AirWatcher" << endl;
        cout << "1. Determiner la fiabilite d'un capteur" << endl;
        cout << "2. Calculer la qualite de l'air" << endl;
        cout << "3. Quitter l'application" << endl;
        cout << "Veuillez entrer votre choix : ";
        cin >> choix;

        switch (choix)
        {
            case 1:
            {
                string sensorId;
                float ecartMax;

                // Saisie et validation de l'ID capteur
                do {
                    cout << "Veuillez entrer l'identifiant du capteur : ";
                    cin >> sensorId;
                    if (!service.verifierExistenceCapteur(sensorId)) {
                        cout << "Capteur '" << sensorId << "' inconnu. Veuillez reessayer." << endl;
                    }
                } while (!service.verifierExistenceCapteur(sensorId));

                // Saisie des paramètres
                cout << "Veuillez entrer le rayon de recherche (en km) : ";
                cin >> rayon;
                cout << "Veuillez entrer l'ecart maximum en pourcentage (ex: 10 pour 10%) : ";
                cin >> ecartMax;

                // Saisie date début
                cout << "Date de debut (jj/mm/yyyy) : ";
                date.lireDate(jour, mois, annee);
                cout << "Heure de debut (hh:mm) : ";
                date.lireHeure(heure, minute, seconde);
                dateDebut = Date(annee, mois, jour, heure, minute, seconde);

                // Saisie et validation date fin
                do {
                    cout << "Date de fin (jj/mm/yyyy) : ";
                    date.lireDate(jour, mois, annee);
                    cout << "Heure de fin (hh:mm) : ";
                    date.lireHeure(heure, minute, seconde);
                    dateFin = Date(annee, mois, jour, heure, minute, seconde);
                    if (!(dateDebut < dateFin)) {
                        cout << "Date de fin invalide, celle-ci doit etre posterieure a la date de debut ! " << endl;
                    }
                } while (!(dateDebut < dateFin));

                // Appel service
                int resultat = service.determinerFiabiliteCapteur(sensorId, rayon, ecartMax, dateDebut, dateFin);

                switch (resultat)
                {
                    case 0:
                        cout << "Erreur : pas assez de donnees pour ce capteur." << endl;
                        break;
                    case 1:
                        cout << "Le capteur est FIABLE." << endl;
                        break;
                    case 2:
                        cout << "Le capteur est NON FIABLE." << endl;
                        break;
                }

                break;
            }

            case 2:
            {
                // Saisie coordonnées et validation du rayon
                cout << "Veuillez entrer la latitude : ";
                cin >> latitude;
                cout << "Veuillez entrer la longitude : ";
                cin >> longitude;
                do {
                    cout << "Veuillez entrer le rayon autour de ce point (km) : ";
                    cin >> rayon;
                    if (rayon <= 0) cout << "Le rayon doit etre superieur a 0 ! " << endl;
                } while (rayon <= 0);

                // Saisie date début
                cout << "Veuillez entrer la date de debut (jj/mm/yyyy) : ";
                date.lireDate(jour, mois, annee);
                cout << "Veuillez entrer l'heure de debut (hh:mm) : ";
                date.lireHeure(heure, minute, seconde);
                dateDebut = Date(annee, mois, jour, heure, minute, seconde);

                // Saisie et validation date fin
                do {
                    cout << "Veuillez entrer la date de fin (jj/mm/yyyy) : ";
                    date.lireDate(jour, mois, annee);
                    cout << "Veuillez entrer l'heure de fin (hh:mm) : ";
                    date.lireHeure(heure, minute, seconde);
                    dateFin = Date(annee, mois, jour, heure, minute, seconde);
                    if (!(dateDebut < dateFin)) {
                        cout << "Date de fin invalide, celle-ci doit etre posterieure a la date de debut ! " << endl;
                    }
                } while (!(dateDebut < dateFin));

                // Appel service

                int qualite = service.calculerQualiterAir(latitude, longitude, rayon, dateDebut, dateFin);
                if (qualite == -1) {
                    cout << "Impossible de calculer la qualite de l'air : donnees insuffisantes ! " << endl;
                } else {
                    cout << "Indice moyen sur la periode : " << qualite << endl;
                }

                break;
            }

            case 3:
                cout << "Merci d'avoir utilise l'application AirWatcher, au revoir et a bientot !!!" << endl;
                continuer = false;
                break;

            default:
                cout << "Choix invalide, veuillez reessayer." << endl;
                break;
        }
    }
} //----- Fin de la méthode application