#include "database.h"

Database::Database(const string& fileName) : fileCheck(fileName),
    fileName(fileName), session("SQLite", fileName) {
}

FileCheck::FileCheck(const string& f) {
    ifstream fs(f);
    if (!fs) {
        throw DatabaseException("ERROR: Filename or path does not exist.");
    }
}

City Database::getCity(int id) {
    string name, country;
    double lon, lat;
    session << "SELECT name, country, lon, lat FROM city WHERE city_id = ?",
            into(name), into(country), into(lon), into(lat), use(id), now;
    City c(id, name, country, lon, lat);

    return c;
}

map<int, string> Database::getAllCities() {
    // TODO: rewrite this and burn any evidence it was ever written
    map<int, string> cityMap;
    std::vector<int> idVec;
    std::vector<string> nameVec;
    session << "SELECT city_id, name FROM city", into(idVec), into(nameVec), now;
    for (int i = 0; i < idVec.size(); ++i) {
        cityMap[idVec[i]] = nameVec[i];
    }
    return cityMap;
}

std::vector<Weatherview> Database::getAllWeatherviews() {
    std::vector<Weatherview> views;
    return views;
}



