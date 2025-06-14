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


//----------------------------------------------------- Méthodes publiques


int Service::determinerFiabiliteCapteur(string sensorId, float radius, float ecartMax, Date debut, Date fin)
// Algorithme : on prend les capteurs voisins dans le radius, on calcule l'indice ATMO moyen
//              et compare avec la qualite de ce capteur avec un ecart max
//              renvoie 0 si erreue (sensorId non valide, pas de capteurs proches ou pas assez de donnees), 1 si fiable et 2 sinon
//{
//} //----- Fin de Méthode
{    
    // Récupérer le capteur associé à sensorId
    Sensor* s = data.getSensorById(sensorId);
    if (s == nullptr) return 0;

    int qS = calculerQualiterParCapteur(s, debut,fin);
    if (qS == -1) return 0; // Si pas de donnée pour ce capteur dans cette période -> inutile de continuer

    // On récupère les capteurs proches
    vector<Sensor*> capteursProches = this->capteursProches(s->getLatitude(),s->getLongitude(),radius);
    if (capteursProches.size() == 0) return 0; 

    //Calculer le moyen et comparer
    int sum = 0;
    int count = 0;
    for (Sensor* capteur : capteursProches)
    {
        if (capteur == s) continue; // on skip le capteur dont on doit déterminer l'efficacité
        int atmo = calculerQualiterParCapteur(capteur,debut, fin); 
        if (atmo == -1) continue;
        sum += atmo;
        count++;
    }
    if (count < 3) return 0; // Il faut au minimum 3 indices ATMO pour comparer

    float moyen = (float)sum/count;

    if (qS < moyen * (1 - ecartMax / 100.0) || qS > moyen * (1 + ecartMax / 100.0)) return 2;
    else return 1;  // Fiable
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
        if (!capteur->getEstDefectueux())
        {
            int qualite = calculerQualiterParCapteur(capteur, start, end);
            
            // On ne prend en compte que les capteurs valides (qualité non -1)
            if (qualite != -1) {
                totalQualite += qualite;
                capteurCount++;
            }
        }
    }

    // Si aucun capteur valide, on retourne une erreur
    if (capteurCount == 0) return -1;

    // Moyenne des indices de qualité des capteurs
    return static_cast<int>(round(totalQualite / capteurCount));
}


bool Service::verifierExistenceCapteur(string sensorId)
{
    return data.getSensorsMap().find(sensorId) != data.getSensorsMap().end();
}

// NON IMPLEMENTE
vector<Measurement> Service::observerImpactAir()
{
    // Return vide pour éviter les warning
    return vector<Measurement>();
}

// NON IMPLEMENTE
unordered_map<Sensor*,float> Service::indentifierCapteursSimilaires(string sensorId)
{
    // Return vide pour éviter les warning
    return {};
}


void Service::bannirCapteur(string sensorId)
{
    Sensor * sensor = data.getSensorById(sensorId);
    if (sensor != nullptr)
    {
        sensor->desactiverCapteur();
    }
}

// NON IMPLEMENTE
int Service::consulterRecompense(string userName)
{
    // Return vide pour éviter les warning
    return -1;
}


//------------------------------------------------- Surcharge d'opérateurs

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

    // Type = size_t pour éviter le warning de comparaison avec des types signés différents
    for (size_t i = 0; i < seuilsPolluant.size(); ++i)
    {
        if (value >= seuilsPolluant[i].min && value <= seuilsPolluant[i].max)
            return static_cast<int>(i + 1); // L’indice ATMO commence à 1
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

double Service::distance(float latitude1, float longitude1, float latitude2, float longitude2) {
    const double R = 6371.0; // Earth radius in km
    const double to_rad = M_PI / 180.0;

    double phi1 = latitude1 * to_rad;
    double phi2 = latitude2 * to_rad;
    double d_phi = (latitude2 - latitude1) * to_rad;
    double d_lambda = (longitude2 - longitude1) * to_rad;

    double a = sin(d_phi / 2) * sin(d_phi / 2) +
               cos(phi1) * cos(phi2) *
               sin(d_lambda / 2) * sin(d_lambda / 2);
    double c = 2 * asin(sqrt(a));

    return R * c;
}
