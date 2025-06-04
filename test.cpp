#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include "Data.h"
#include "Date.h"
#include "Service.h"


TEST_CASE("Classe Data") 
{

    Data data;
    Date date;

    
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
}

TEST_CASE("Classe Date")
{
    SUBCASE("Test Surcharge Date")
    {
        Date date1(2023, 10, 1, 12, 0, 0);
        Date date2(2023, 10, 1, 12, 0, 0);
        Date date3(2023, 10, 2, 12, 0, 0);

        CHECK(date1 == date2);
        CHECK(date1 < date3);
        CHECK(date3 > date1);
    }
}

TEST_CASE("Classe Service")
{
    SUBCASE("Calculer ATMO avec 1 capteur : les dates restreignent au seul capteur 64")
    {
        Service service("./dataset/_fileGroupeTestFiabilite.csv");
        Date debut(2019, 11, 30, 12, 0, 0);
        Date fin(2019, 13, 30, 12, 0, 0);
        
        // Les dates restreingnent au seul capteur 64
        CHECK(service.calculerQualiterAir(46.4, 1.8, 1, debut, fin) == 9);

    }

    SUBCASE("Calculer ATMO avec 1 capteur : les dates correspondent aux 2 capteurs 64 et 0, mais radius sélectionne uniquement 0")
    {
        Service service("./dataset/_fileGroupeTestFiabilite.csv");
        Date debut(2010, 11, 30, 12, 0, 0);
        Date fin(2035, 13, 30, 12, 0, 0);
        
        CHECK(service.calculerQualiterAir(44, -1, 0.1, debut, fin) == 8);
    }

    SUBCASE("Calculer ATMO avec 2 capteur")
    {
        CHECK(true);
    }

    SUBCASE("Calculer ATMO : pas de capteur aux alentours")
    {
        CHECK(true);
    }

    SUBCASE("Calculer ATMO : pas de donnée dans les dates données")
    {
        CHECK(true);
    }

    SUBCASE("Test méthode distance") 
    {
        Service s("./dataset/_fileGroupeTestFiabilite.csv");
        // Correspond to the distance between Sensor 16 and 31 -> 290.1 km with 1% error allowed
        CHECK(s.distance(44.4, 3.2, 45.2, -0.3) == doctest::Approx(290.1).epsilon(0.01));
    }

    SUBCASE("Test méthode getCapteurProches")
    {
        Service s("./dataset/_fileGroupeTestFiabilite.csv");
        CHECK(s.capteursProches(44., -1., 1).size() == 1);

        CHECK(s.capteursProches(49., -9., 1).size() == 0);
        
        CHECK(s.capteursProches(44., -1., 50).size() == 2);
    }

    SUBCASE("Test méthode vérifier existance par capteur")
    {
        Service s("./dataset/_fileGroupeTestFiabilite.csv");

        CHECK(s.verifierExistenceCapteur("Sensor3"));

        CHECK(!s.verifierExistenceCapteur("Excellent project"));
    }

    SUBCASE("Test bannir sensor")
    {
        Service s("./dataset/_fileGroupeTestFiabilite.csv");

        // Get sensor0
        Sensor * sensor = s.capteursProches(44., -1., 1)[0]; 
        CHECK(!sensor->getEstDefectueux());
        s.bannirCapteur("Sensor0");
        CHECK(sensor->getEstDefectueux());

    }
}