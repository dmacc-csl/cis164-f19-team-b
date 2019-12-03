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
    cout << "Test 01: getCity(id) -> name... ";
    City c1 = database.getCity(707860);
    if (c1.getName().compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 2
    cout << "Test 02: getCity(id) -> lon... ";
    City c2 = database.getCity(519188);
    if (c2.getLon() == 37.666668) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 3
    cout << "Test 03: getAllCities() -> count... ";
    map<int, string> cm1 = database.getAllCities();
    if (cm1.count(707860) == 1) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }
    // TEST 4
    cout << "Test 04: getAllCities() -> at... ";
    map<int, string> cm2 = database.getAllCities();
    if (cm2.count(707860) == 1 && cm2.at(707860).compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 5
    cout << "Test 05: getAllCities() -> find by name... ";
    map<int, string> cm3 = database.getAllCities();
    int v1 = -1;
    for (auto it = cm3.begin(); it != cm3.end(); ++it) {
        if (it->second.compare("Hurzuf") == 0) {
            v1 = it->first;
            break;
        }
    }
    if (v1 == 707860) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 6
    cout << "Test 06: getWeatherview(id) -> getName... ";
    Weatherview v = database.getWeatherview(1);
    if (v.getName().compare("5 day forecast") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 7
    cout << "Test 07: getAllWeatherviews() -> [].getName... ";
    std::vector<Weatherview> views = database.getAllWeatherviews();
    if (views[1].getName().compare("5 day forcast") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    /*
    City tc1 = database.getCity(707860);
    Weatherview tv1 = database.getWeatherview(1);
    Tile t1(tv1, tc1);
    database.insertTile(t1, 0);
    */

    // TEST 8
    cout << "Test 08: getTile() -> getName... ";
    Tile* t2 = database.getTile(1);
    if(t2->getCity().getName().compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    cout << "\n\nStarting getAllDashboards" << endl;
    std::vector<Dashboard> dv1 = database.getAllDashboards();
    //for (auto it = dv1.begin(); it != dv1.end(); ++it) {
    /*
    for (Dashboard d : dv1) {
        cout << "startloop" << endl;
        cout << d.getName() << endl;
        cout << "endloop" << endl;
    }
    */
    cout << dv1[0].getName() << endl;

    cout << "blah blah" << endl;



    return 0;
}
