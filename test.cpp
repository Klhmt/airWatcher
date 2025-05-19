#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include "Data.h"


TEST_CASE("Testing data") 
{
    Data data;
    CHECK(data.loadProviderAndAirWatcher("/home/klem/Documents/GL/5_projet_dataset/providers.csv", "/home/klem/Documents/GL/5_projet_dataset/cleaners.csv"));
    CHECK(data.loadPrivateOwnersAndSensors("/home/klem/Documents/GL/5_projet_dataset/users.csv", "/home/klem/Documents/GL/5_projet_dataset/sensors.csv"));
    CHECK(data.getSensors().size() == 100);
}