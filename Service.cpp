/*************************************************************************
                           Service  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Service> (fichier Service.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Service.h"
#include <cmath>
//------------------------------------------------------------- Constantes
//----------------------------------------------------------------- PUBLIC

//une function distance:
int distance(int x1, int y1, int x2, int y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}


//----------------------------------------------------- Méthodes publiques
// type Service::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode


int Service::determinerFiabiliteCapteur(string sensorId, float radius, float ecartMax, Date debut, Date fin)
// Algorithme : on prend les capteurs voisins dans le radius, on calcule leur qualite moyen 
//              et compare avec la qualite de ce capteur avec un ecart max
//              renvoie 0 si erreue (sensorId non valide, pas de capteurs proches ou pas assez de donnees), 1 si fiable et 2 sinon
//{
//} //----- Fin de Méthode
{    
    //Get le capteur a determiner et ses voisins dans le radius
    Sensor* s = data.getSensorById(sensorId);
    if (s == nullptr) return 0;
    vector<Sensor*> capteursProches = this->capteursProches(s->getLatitude(),s->getLongitude(),radius);
    if (capteursProches.size()==0) return 0;

    //Calculer le moyen et comparer
    int sum = 0;
    int count = 0;
    for (Sensor* capteur : capteursProches)
    {
        sum += calculerQualiterParCapteur(capteur,debut, fin);
        count++;
    }
    int moyen = sum/count;
    int qS = calculerQualiterParCapteur(s, debut,fin);
    if((qS<moyen*(1+ecartMax/100)) && (qS>moyen*(1-ecartMax/100))) return 1;
    else return 0;
}


int Service::calculerQualiterAir(float lat, float lon, float radius, Date start, Date end)
{
    // Récupère les capteurs proches dans le rayon autour du point (lat, lon)
    vector<Sensor*> capteurs = capteursProches(lat, lon, radius);
    
    // Si aucun capteur trouvé, on retourne une erreur
    if (capteurs.empty()) return -1;

    float totalQualite = 0;
    int capteurCount = 0;

    // Parcours chaque capteur pour calculer sa qualité d’air individuelle
    for (Sensor* capteur : capteurs)
    {
        int qualite = calculerQualiterParCapteur(capteur, start, end);
        
        // On ne prend en compte que les capteurs valides (qualité non -1)
        if (qualite != -1) {
            totalQualite += qualite;
            capteurCount++;
        }
    }

    // Si aucun capteur valide, on retourne une erreur
    if (capteurCount == 0) return -1;

    // Moyenne des indices de qualité des capteurs
    return static_cast<int>(totalQualite / capteurCount);
}


bool Service::verifierExistenceCapteur(string sensorId)
{
    return data.getSensorsMap().find(sensorId) != data.getSensorsMap().end();
}


vector<Measurement> Service::observerImpactAir()
{
    
}


unordered_map<Sensor*,float> Service::indentifierCapteursSimilaires(string sensorId)
{

}


void Service::bannirCapteur(string sensorId)
{
    Sensor * sensor = data.getSensorById(sensorId);
    if (sensor != nullptr)
    {
        sensor->desactiverCapteur();
    }
}


int Service::consulterRecompense(string userName)
{

}


//------------------------------------------------- Surcharge d'opérateurs
Service & Service::operator = ( const Service & unAirCleaner )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur

Service::Service ( const Service & unAirCleaner )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Service>" << endl;
#endif
} //----- Fin de Service (constructeur de copie)

Service::Service( )
{
    
}

Service::Service (const string& filePath)
    : data(filePath)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Service>" << endl;
#endif
} //----- Fin de Service


Service::~Service ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Service>" << endl;
#endif
} //----- Fin de ~Service


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

vector<Sensor*> Service::capteursProches(float lat, float lon, float radius)
{
    
    vector<Sensor*> listCapteurProche;
    vector<Sensor*> allCapteur = data.getSensors();

    for (Sensor* capteur : allCapteur)   
    {
        if (distance(lat,lon,capteur->getLatitude(),capteur->getLongitude()) < radius)
        {
            listCapteurProche.push_back(capteur);
        } 
    }
    return listCapteurProche;
}

int Service::convertirEnIndiceATMO(const string& pollutant, float value)
{
    struct Seuil { float min, max; };
    unordered_map<string, vector<Seuil>> seuils = {
        {"O3", {{0,29},{30,54},{55,79},{80,104},{105,129},{130,149},{150,179},{180,209},{210,239},{240,1e6}}},
        {"SO2", {{0,39},{40,79},{80,119},{120,159},{160,199},{200,249},{250,299},{300,399},{400,499},{500,1e6}}},
        {"NO2", {{0,29},{30,54},{55,84},{85,109},{110,134},{135,164},{165,199},{200,274},{275,399},{400,1e6}}},
        {"PM10", {{0,6},{7,13},{14,20},{21,27},{28,34},{35,41},{42,49},{50,64},{65,79},{80,1e6}}}
    };

    const vector<Seuil>& seuilsPolluant = seuils[pollutant];

    for (int i = 0; i < seuilsPolluant.size(); ++i)
    {
        if (value >= seuilsPolluant[i].min && value <= seuilsPolluant[i].max)
            return i + 1; // L’indice ATMO commence à 1
    }

    return -1; // Valeur hors bornes, ou pas de polluant correspondant
}


int Service::calculerQualiterParCapteur(Sensor* sensor, Date start, Date stop)
{
    // Récupère la map des mesures : sensorID → {Date → [Measurements]}
    dataStructure mesures = data.getMeasurements();
    dataStructure::iterator it = mesures.find(sensor->getSensorId());
    
    // Si le capteur n'a pas de mesure, on retourne une erreur
    if (it == mesures.end()) return -1;

    map<Date, vector<Measurement*>> mesuresCapteur = it->second;

    // Regrouper les mesures par type de polluant : nom_polluant : [mesures]
    unordered_map<string, vector<float>> mesuresParPolluant;
    
    map<Date, vector<Measurement*>>::iterator itStart = mesuresCapteur.lower_bound(start);
    map<Date, vector<Measurement*>>::iterator itEnd = mesuresCapteur.upper_bound(stop);

    // On utilise le fait que la map soit ordonnée
    for (map<Date, vector<Measurement*>>::iterator it = itStart; it != itEnd; ++it) {
        
        for (Measurement* mesure : it->second)
        {
            mesuresParPolluant[mesure->getAttribute()].push_back(mesure->getValue());
        }
        
    }

    // Aucune mesure sur la période
    if (mesuresParPolluant.empty()) return -1;

    int indiceATMO = -1;

    // Pour chaque polluant mesuré
    for (const pair<const string, vector<float>>& pair : mesuresParPolluant)
    {
        const string& attr = pair.first;
        const vector<float>& valeurs = pair.second;

        // Calcul de la moyenne des mesures pour ce polluant
        float sommeMesures = 0;
        for (float v : valeurs) sommeMesures += v;
        float moyenne = sommeMesures / valeurs.size();

        // Conversion de la moyenne en indice ATMO
        int indice = convertirEnIndiceATMO(attr, moyenne);

        // On garde l'indice max
        if (indice > indiceATMO)
        {
            indiceATMO = indice;
        }
    }

    return indiceATMO;
}