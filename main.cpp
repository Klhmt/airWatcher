#include <iostream>

#include "UI.h"

using namespace std;


int main()
{
    // Ici se trouvera l'appel à la classe UI
    UI ui;

    if (ui.authentification() == false)
    {
        cout << "Erreur d'authentification" << endl;
        return 1;
    }

    ui.application();
    return 0;
}