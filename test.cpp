#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include "Data.h"
#include "Date.h"

void printDataStructure(const dataStructure& data)
{
    for (const auto& sensorEntry : data)
    {
        const string& sensorID = sensorEntry.first;
        const map<Date, vector<Measurement*>>& measurementsByDate = sensorEntry.second;

        cout << "Sensor ID: " << sensorID << endl;

        for (const auto& dateEntry : measurementsByDate)
        {
            const Date& date = dateEntry.first;
            const vector<Measurement*>& measurements = dateEntry.second;

            cout << "  Date: " << date << endl; // ou cout << date << si operator<< existe

            for (const Measurement* m : measurements)
            {
                // À adapter selon ce que Measurement contient
                cout << "    ";
                cout << "Type: " << m->getAttribute() << ", ";
                cout << "Value: " << m->getValue() << endl;
            }
        }

        cout << "----------------------------------" << endl;
    }
}



TEST_CASE("Testing data") 
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
        // nécessaire avant de charger les mesures
        data.loadPrivateOwnersAndSensors("./dataset/users.csv", "./dataset/sensors.csv");
        data.loadMeasurements("./dataset/measurements_test.csv");
        dataStructure donnees = data.getMeasurements();
        CHECK(donnees.size() == 2);
        //Date d = Date(2019, 12, 01, 12, 00, 00);
        //cout << donnees["Sensor64"][d][0]->getValue() << endl;
        
        
        //CHECK(data.loadMeasurements("./dataset/measurements_test.csv"));
        //CHECK(data.getMeasurements().size() == 2);
        //CHECK(data.getMeasurements()["Sensor0"].size() == 6);
    }
}