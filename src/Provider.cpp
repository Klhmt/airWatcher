//---------- Réalisation de la classe <Provider> (fichier Provider.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Provider.h"

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs
Provider & Provider::operator = ( const Provider & unProvider )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Provider::Provider( const string name)
{
    providerName = name;
}


Provider::Provider ( const Provider & unProvider )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Provider>" << endl;
#endif
} //----- Fin de Provider (constructeur de copie)


Provider::Provider ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Provider>" << endl;
#endif
} //----- Fin de Provider


Provider::~Provider ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Provider>" << endl;
#endif
} //----- Fin de ~Provider


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées