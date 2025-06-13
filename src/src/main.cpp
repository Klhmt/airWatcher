#include <iostream>
#include "Service.h"
#include "UI.h"

int main()
{
    
    Service service("dataset/_fileGroupOrigine.csv");

    UI ui(service);

    if (ui.authentification())
    {
        ui.application();
    }
    else
    {
        std::cerr << "Erreur d'authentification ! \n";
        return 1;
    }

    return 0;
}
