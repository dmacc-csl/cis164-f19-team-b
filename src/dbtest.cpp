#include <iostream>
#include "database.h"
#pragma comment(lib, "ws2_32.lib") // for Visual Studio, pulls in a Windows library
#pragma comment(lib, "IPHLPAPI.lib") // for Visual Studio, pulls in a Windows library

using namespace std;

int main(int argc, char* argv[]) {

    string dbfile = "dashboards.db";
    if (argc > 1) {
        dbfile = argv[1];
    }
    Poco::Data::SQLite::Connector::registerConnector();
    Database database(dbfile);

	// Test data to run without python script
	database.insertCity(City(707860, "Hurzuf", "TEST", 33.3, 33.3));
	

	//CM TEST 1: INSERT CITY
	cout << "Test 01: Inserting City into database" << endl;
	database.insertCity(City(519188, "TEST", "TEST", 37.666668, 33.3));
	City c1 = database.getCity(519188);
	if (c1.getName().compare("TEST") == 0) {
		cout << "Insert successful" << endl;
	}
	else {
		cout << "Insert failed" << endl;
	}

	//CM TEST 2: DELETE CITY
	cout << "Test 02: Deleting City from database" << endl;
	database.deleteCity(519188);
	std::map<int, string> v1 = database.getAllCitiesI();
	if (v1.count(519188) == 0) {
		cout << "Delete successful" << endl;
	}
	else {
		cout << "Delete failed" << endl;
	}

	//CM TEST 3: ATTEMPT TO RETRIEVE NON-EXISTANT CITY
	cout << "Test 03: Attempt to get non-existant city from database" << endl;
	database.deleteCity(519188);
	City c2 = database.getCity(519188);
	if (c2.getName().empty()) {
		cout << "ERROR: City does not exist" << endl;
	}
	else {
		cout << "City exists?" << endl;
	}

	/*
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
    cout << "Test 03: getAllCitiesI() -> count... ";
    map<int, string> cm1 = database.getAllCitiesI();
    if (cm1.count(707860) == 1) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }
    // TEST 4
    cout << "Test 04: getAllCitiesI() -> at... ";
    map<int, string> cm2 = database.getAllCitiesI();
    if (cm2.count(707860) == 1 && cm2.at(707860).compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 5
    cout << "Test 05: getAllCitiesI() -> find by name... ";
    map<int, string> cm3 = database.getAllCitiesI();
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

    // SETUP
    database.clearTables();
    City dc1 = database.getCity(707860);
    Weatherview dw1 = database.getWeatherview(1);
    Tile dt1(dw1, dc1);
    std::vector<Tile> dv1;
    dv1.push_back(dt1);
    Dashboard db1("testboard1", dv1);
    database.insertDashboard(db1);

    // TEST 8
    cout << "Test 08: getTile() -> getName... ";
    Tile t2 = database.getTile(1);
    if(t2.getCity().getName().compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 9
    cout << "Test 09: getAllDashboards() -> getName... ";
    std::vector<Dashboard> dv2 = database.getAllDashboards();
    if (dv2[0].getName().compare("testboard1") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

    // TEST 10
    cout << "Test 10: getAllDashboards() -> getTiles.getCity.getName... ";
    std::vector<Dashboard> dv3 = database.getAllDashboards();
    if (dv3[0].getTiles()[0].getCity().getName().compare("Hurzuf") == 0) {
        cout << "PASSED" << endl;
    } else {
        cout << "FAILED" << endl;
    }

	*/

    /*
    for (Dashboard d : dv2) {
        cout << d.getName() << endl;
        cout << d.getTiles()[0].getCity().getName() << endl;
    }
    */
	


    return 0;
}
