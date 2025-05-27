#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include "Data.h"
#include "Date.h"
#include "Service.h"


TEST_CASE("Testing data") 
{

    Data data;
    Service service;
    
    SUBCASE("Chargement des Provider & Aircleaners")
    {
        CHECK(data.loadProviderAndAirWatcher("./dataset/providers.csv", "./dataset/cleaners.csv"));
        CHECK(data.getAirCleaner().size() == 2);
        CHECK(data.getProvider().size() == 2);
    }
    SUBCASE("Chargement des Private Owners et des Sensors")
    {
        CHECK(data.loadPrivateOwnersAndSensors("./dataset/users.csv", "./dataset/sensors.csv"));
        CHECK(data.getSensors().size() == 100);
    }

    SUBCASE("Chargement des Measurements")
    {
        data.loadPrivateOwnersAndSensors("./dataset/users.csv", "./dataset/sensors.csv");
        data.loadMeasurements("./dataset/measurements_test.csv");
                
        CHECK(data.getMeasurements().size() == 2);

        CHECK(data.getMeasurements()["Sensor64"].size() == 2);
        
    }

//     SUBCASE("calculer le qualiter d'un capteur")
//     {
//         service.data.loadMeasurements("./dataset/measurements_test.csv");
        
//         CHECK(service.calculerQualiterAir(service.data.getSensors()) == 53.0625);
//     }

//     SUBCASE("Calculer la fiabilite d'un capteur")
//     {

//     }

}