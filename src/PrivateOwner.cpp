//---------- Réalisation de la classe <PrivateOwner> (fichier PrivateOwner.cpp) ------------
//---------------------------------------------------------------- INCLUDE
//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "PrivateOwner.h"

//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//-------------------------------------------- Constructeur
PrivateOwner::PrivateOwner(string name, int pts)
// Algorithme :
//
{
#ifdef MAP
cout << "Appel au constructeur paramétré de <PrivateOwner>" << endl;
#endif

    userName = name;
    points = pts;
} //----- Fin du constructeur

PrivateOwner::PrivateOwner()
{
#ifdef MAP
cout << "Appel au constructeur par défaut de <PrivateOwner>" << endl;
#endif
}


//-------------------------------------------- Destructeur
PrivateOwner::~PrivateOwner()
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <PrivateOwner>" << endl;
#endif
} //----- Fin du destructeur

