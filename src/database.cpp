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
    if (idVec.size() == 0) {
        throw DatabaseException("ERROR: No city data in database.");
    }
    if (idVec.size() != nameVec.size()) {
        throw DatabaseException("ERROR: Null of missing value in database.");
    }
    for (int i = 0; i < idVec.size(); ++i) {
        cityMap[idVec[i]] = nameVec[i];
    }
    return cityMap;
}

Weatherview Database::getWeatherview(int id) {
    string name, description, callString;
    // TODO: try/catch?
    session << "SELECT name, description, call_string FROM weatherview WHERE weatherview_id = ?",
            into(name), into(description), into(callString), use(id), now;
    Weatherview v(id, name, description, callString);
    return v;
}

std::vector<Weatherview> Database::getAllWeatherviews() {
    Statement select(session);
    select << "SELECT * FROM weatherview", now;
    RecordSet rs(select);
    std::vector<Weatherview> views;
    for (auto it = rs.begin(); it != rs.end(); ++it) {
        Weatherview v(it->get(0), it->get(1), it->get(2), it->get(3));
        views.push_back(v);
    }
    return views;
}



