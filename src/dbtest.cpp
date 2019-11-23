#include <iostream>
#include "database.h"
using namespace std;

int main(int argc, char* argv[]) {
    string dbfile = "dashboards.db";
    if (argc > 1) {
        dbfile = argv[1];
    }
    Poco::Data::SQLite::Connector::registerConnector();
    Database database(dbfile);


    // TEST 1
    cout << "Test 1: getCity(id) -> name... ";
    City c1 = database.getCity(707860);
    if (c1.getName().compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 2
    cout << "Test 2: getCity(id) -> lon... ";
    City c2 = database.getCity(519188);
    if (c2.getLon() == 37.666668) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 3
    cout << "Test 3: getAllCities() -> count... ";
    map<int, string> cm1 = database.getAllCities();
    if (cm1.count(707860) == 1) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }
    // TEST 4
    cout << "Test 4: getAllCities() -> at... ";
    map<int, string> cm2 = database.getAllCities();
    if (cm2.count(707860) == 1 && cm2.at(707860).compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 5
    cout << "Test 5: getAllCities() -> find by name... ";
    map<int, string> cm3 = database.getAllCities();
    int v1 = -1;
    for (auto it = cm3.begin(); it != cm3.end(); ++it) {
        if (it->second.compare("Hurzuf")) {
            v1 = it->first;
            break;
        }
    }
    if (v1 == 707860) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }



}
