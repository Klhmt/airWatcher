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

//------------------------------------------------------ Include personnel
#include "UI.h"
#include "Date.h"


//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeur par défaut
UI::UI()
// Algorithme :
//
{
    #ifdef MAP
    cout << "Appel au constructeur par défaut de <UI>" << endl;
    #endif
} //----- Fin du constructeur par défaut


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
    Date date, dateDebut, dateFin;
    int jour, mois, annee;
    int heure, minute, seconde;

    int numeroCapteur;

    float latitude, longitude, rayon;

    bool verificationDate = false;

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
            cout << "Veuillez entrer le numero du capteur : ";
            cin >> numeroCapteur;

            
            // Appel méthode determinerFiabiliteCapteur

            break;

        case 2:
            cout << "Veuillez entrer la latitude : ";
            cin >> latitude;

            cout << "Veuillez entrer la longitude : ";
            cin >> longitude;

            cout << "Veuillez entrer le rayon autour de ce point : ";
            cin >> rayon;

            while (rayon <= 0)
            {
                cout << "Le rayon doit etre superieur a 0, veuillez reessayer : ";
                cin >> rayon;
            }

            cout << "Veuillez entrer la date de debut (jj/mm/yyyy) : "; 
            date.lireDate(jour, mois, annee);

            cout << "Veuillez entrer l'heure de debut (hh:mm) : ";
            date.lireHeure(heure, minute, seconde);

            dateDebut = Date(annee, mois, jour, heure, minute, seconde);

            cout << "Veuillez entrer la date de fin (jj/mm/yyyy) : ";
            date.lireDate(jour, mois, annee);

            cout << "Veuillez entrer l'heure de fin (hh:mm) : ";
            date.lireHeure(heure, minute, seconde);

            dateFin = Date(annee, mois, jour, heure, minute, seconde);

            verificationDate = (dateDebut < dateFin);

            while (!verificationDate)
            {
                cout << "Veuillez mettre une date de fin posterieure a la date de debut : " ;
                date.lireDate(jour, mois, annee);
                
                cout << "Veuillez entrer l'heure de fin (hh:mm) : ";
                date.lireHeure(heure, minute, seconde);

                dateFin = Date(annee, mois, jour, heure, minute, seconde);
                verificationDate = (dateDebut < dateFin);
            }
            

            // Appeler la méthode calculerQualiteAir
            cout << "Affichage des resultats"<<endl;
            break;

        case 3:
            cout << "Merci d'avoir utilise l'application AirWatcher, au revoir et a bientot !!!" << endl;
            break;

        default:
            cout << "Choix invalide, veuillez reessayer." << endl;
            application();
            break;
    }
} //----- Fin de la méthode application

