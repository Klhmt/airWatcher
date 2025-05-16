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
  

//-------------------------------------------- Autres méthodes
void UI::application()
// Algorithme :
//
{
    int choix = 0;
    cout << "-------------------------------------------------" << endl;
    cout << "Bienvenue dans l'application AirWatcher" << endl;
    cout << "1. Methode1" << endl;
    cout << "2. Quitter l'application" << endl;
    cout << "Veuillez entrer votre choix : ";
    cin >> choix;
    switch (choix)
    {
        case 1:
            cout << "Appel Methode 1" << endl;
            // Appeler la méthode pour lancer l'application
            break;
        case 2:
            cout << "Merci d'avoir utilise AirWatcher, au revoir !!!" << endl;
            break;
        default:
            cout << "Choix invalide, veuillez reessayer." << endl;
            application();
            break;
    }
} //----- Fin de la méthode application

