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
            cout << "Appel Methode determinerFiabiliteCapteur" << endl;
            // Appeler la méthode determinerFiabiliteCapteur
            break;

        case 2:
            cout << "Appel Methode calculerQualiteAir" << endl;
            // Appeler la méthode calculerQualiteAir
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

