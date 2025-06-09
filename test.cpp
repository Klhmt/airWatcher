#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include "Data.h"
#include "Date.h"
#include "Service.h"


TEST_CASE("Classe Data") 
{
    Data data;
    
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
    SUBCASE("Méthode calculerQualiterAir : calculer ATMO avec 1 capteur : les dates restreignent au seul capteur 64")
    {
        Service service("./dataset/_fileGroupeTest.csv");
        Date debut(2019, 11, 30, 12, 0, 0);
        Date fin(2019, 13, 30, 12, 0, 0);
        
        // Les dates restreingnent au seul capteur 64
        CHECK(service.calculerQualiterAir(46.4, 1.8, 1, debut, fin) == 9);

    }

    SUBCASE("Méthode calculerQualiterAir : Calculer ATMO avec 1 capteur : les dates correspondent aux 2 capteurs 64 et 0, mais radius sélectionne uniquement 0")
    {
        Service service("./dataset/_fileGroupeTest.csv");
        Date debut(2010, 11, 30, 12, 0, 0);
        Date fin(2035, 13, 30, 12, 0, 0);
        
        CHECK(service.calculerQualiterAir(44, -1, 0.1, debut, fin) == 8);
    }

    SUBCASE("Méthode calculerQualiterAir : Calculer ATMO avec 2 capteur")
    {
        Service service("./dataset/_fileGroupeTest.csv");
        Date debut(2010, 11, 30, 12, 0, 0);
        Date fin(2035, 13, 30, 12, 0, 0);
        
        // Manual calculus : 3 ATMO measures from 2 sensors, 8, 9 => mean ~= 8.5 hence the expected result is 9 (std::round is rounding halfway cases away from zero)
        // See https://en.cppreference.com/w/cpp/numeric/math/round
        CHECK(service.calculerQualiterAir(44, -1, 400, debut, fin) == 9);
    }

    SUBCASE("Méthode calculerQualiterAir : pas de capteur aux alentours")
    {
        Service service("./dataset/_fileGroupeTest.csv");
        Date debut(2010, 11, 30, 12, 0, 0);
        Date fin(2035, 13, 30, 12, 0, 0);

        CHECK(service.calculerQualiterAir(48, -1, 1, debut, fin) == -1);
    }

    SUBCASE("Méthode calculerQualiterAir : pas de donnée dans les dates données")
    {
        Service service("./dataset/_fileGroupeTest.csv");
        Date debut(2001, 11, 30, 12, 0, 0);
        Date fin(202, 13, 30, 12, 0, 0);
        
        CHECK(service.calculerQualiterAir(48, -1, 100000000, debut, fin) == -1);
    }

    SUBCASE("Méthode distance") 
    {
        Service s("./dataset/_fileGroupeTest.csv");
        // Useful online calculator: https://calculator.academy/haversine-distance-calculator/
        // Correspond to the distance between Sensor 16 and 31 -> 290.1 km with 1% error allowed
        CHECK(s.distance(44.4, 3.2, 45.2, -0.3) == doctest::Approx(290.1).epsilon(0.01));
    }

    SUBCASE("Méthode capteursProches")
    {
        Service s("./dataset/_fileGroupeTest.csv");
        CHECK(s.capteursProches(44., -1., 1).size() == 1);

        CHECK(s.capteursProches(49., -9., 1).size() == 0);
        
        CHECK(s.capteursProches(44., -1., 50).size() == 2);
    }

    SUBCASE("Méthode vérifierExistanceCapteur")
    {
        Service s("./dataset/_fileGroupeTest.csv");

        CHECK(s.verifierExistenceCapteur("Sensor3"));

        CHECK(!s.verifierExistenceCapteur("Excellent project"));
    }

    SUBCASE("Méthode bannirCapteur")
    {
        Service s("./dataset/_fileGroupeTest.csv");

        // Get sensor0
        Sensor * sensor = s.capteursProches(44., -1., 1)[0]; 
        CHECK(!sensor->getEstDefectueux());
        s.bannirCapteur("Sensor0");
        CHECK(sensor->getEstDefectueux());

    }
    SUBCASE("Méthode convertirEnIndiceATMO")
    {
        Service s("./dataset/_fileGroupeTest.csv");
        CHECK(s.convertirEnIndiceATMO("O3", 15) == 1);
        CHECK(s.convertirEnIndiceATMO("O3", 42) == 2);
        CHECK(s.convertirEnIndiceATMO("O3", 67) == 3);
        CHECK(s.convertirEnIndiceATMO("O3", 240) == 10);

        CHECK(s.convertirEnIndiceATMO("SO2", 20) == 1);
        CHECK(s.convertirEnIndiceATMO("SO2", 60) == 2);
        CHECK(s.convertirEnIndiceATMO("SO2", 500) == 10);

        CHECK(s.convertirEnIndiceATMO("NO2", 15) == 1);
        CHECK(s.convertirEnIndiceATMO("NO2", 42) == 2);
        CHECK(s.convertirEnIndiceATMO("NO2", 400) == 10);

        CHECK(s.convertirEnIndiceATMO("PM10", 3) == 1);
        CHECK(s.convertirEnIndiceATMO("PM10", 10) == 2);
        CHECK(s.convertirEnIndiceATMO("PM10", 80) == 10);

        CHECK(s.convertirEnIndiceATMO("InvalidPollutant", 50) == -1);
        CHECK(s.convertirEnIndiceATMO("O3", -5) == -1);
    }
    SUBCASE("Méthode CalculerQualiterParCapteur")
    {
        Service service("./dataset/_fileGroupeTest.csv");
        Date debut(2010, 11, 30, 12, 0, 0);
        Date fin(2035, 13, 30, 12, 0, 0);
        
        // Manual calculus : 3 ATMO measures from 2 sensors, 8, 9 => mean ~= 8.5 hence the expected result is 9 (std::round is rounding halfway cases away from zero)
        // See https://en.cppreference.com/w/cpp/numeric/math/round

        // Get sensor0
        Sensor * sensor0 = service.capteursProches(44., -1., 1)[0]; 

        // Get sensor64
        Sensor * sensor64 = service.capteursProches(46.4, 1.8, 1)[0]; 


        CHECK(service.calculerQualiterParCapteur(sensor0, debut, fin) == 8);
        CHECK(service.calculerQualiterParCapteur(sensor64, debut, fin) == 9);

    }
    SUBCASE("Méthode FiabiliteCapteur")
    {
        Service service("./dataset/_fileGroupeTestFiabiliteCapteur.csv");

        Date debut(2010, 11, 30, 12, 0, 0);
        Date fin(2035, 13, 30, 12, 0, 0);

        // Manual calculus -> Sensor 0 = 8; Sensor64 = 2; Sensor5 = 3; Sensor22 = 3; Sensor2 = 8
        // Mean ~ 5,5, max 10% difference -> Sensor64 is unreliable
        CHECK(service.determinerFiabiliteCapteur("Sensor64", 1000, 10, debut, fin) == 2); 
        // Now with 70% difference allowed -> Sensor64 is reliable
        CHECK(service.determinerFiabiliteCapteur("Sensor64", 1000, 70, debut, fin) == 1);

        // Missing data in this new interval
        Date debut2(200, 11, 30, 12, 0, 0);
        Date fin2(203, 13, 30, 12, 0, 0);

        CHECK(service.determinerFiabiliteCapteur("Sensor64", 1000, 10, debut2, fin2) == 0); 

        // No sensor found because of the radius is too small
        CHECK(service.determinerFiabiliteCapteur("Sensor64", 0.1, 10, debut2, fin2) == 0); 


    }
}