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
    session << "SELECT name, country, lon, lat "
               "FROM city "
               "WHERE city_id = ?",
            into(name), into(country), into(lon), into(lat), use(id), now;
    City c(id, name, country, lon, lat);

    return c;
}

std::vector<City> Database::getCityByName(string cName) {
    std::vector<City> cities;
    Statement select(session);
    select << "SELECT * "
              "FROM city"
              "WHERE name = ?",
            use(cName), now;
    RecordSet rs(select);
    for (auto it = rs.begin(); it != rs.end(); ++it) {
        City c(it->get(0), it->get(1), it->get(2), it->get(3), it->get(4));
        cities.push_back(c);
    }
    return cities;
}

map<int, string> Database::getAllCitiesI() {
    // TODO: rewrite this and burn any evidence it was ever written
    map<int, string> cityMap;
    std::vector<int> idVec;
    std::vector<string> nameVec;
    session << "SELECT city_id, name  "
               "FROM city",
            into(idVec), into(nameVec), now;
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

map<string, int> Database::getAllCitiesN() {
    // TODO: rewrite this and burn any evidence it was ever written
    map<string, int> cityMap;
    std::vector<int> idVec;
    std::vector<string> nameVec;
    session << "SELECT city_id, name  "
               "FROM city",
            into(idVec), into(nameVec), now;
    if (idVec.size() == 0) {
        throw DatabaseException("ERROR: No city data in database.");
    }
    if (idVec.size() != nameVec.size()) {
        throw DatabaseException("ERROR: Null of missing value in database.");
    }
    for (int i = 0; i < idVec.size(); ++i) {
        cityMap[nameVec[i]] = idVec[i];
    }
    return cityMap;
}

Weatherview Database::getWeatherview(int id) {
    string name, description, callString;
    // TODO: try/catch?
    session << "SELECT name, description, call_string "
               "FROM weatherview "
               "WHERE weatherview_id = ?",
            into(name), into(description), into(callString), use(id), now;
    Weatherview v(id, name, description, callString);
    return v;
}

std::vector<Weatherview> Database::getAllWeatherviews() {
    Statement select(session);
    select << "SELECT * "
              "FROM weatherview",
            now;
    RecordSet rs(select);
    std::vector<Weatherview> views;
    for (auto it = rs.begin(); it != rs.end(); ++it) {
        Weatherview v(it->get(0), it->get(1), it->get(2), it->get(3));
        views.push_back(v);
    }
    return views;
}

void Database::insertTile(Tile& t, int p) {
    int wId = t.getWeatherview().getId();
    int cId = t.getCity().getId();
    session << "INSERT INTO tile (weatherview_id, city_id, dashboard_id) "
               "VALUES (?, ?, ?)",
            use(wId), use(cId), use(p), now;
}

Tile Database::getTile(int id) {
    int wId, cId, cLon, cLat;
    string wName, wDescription, wCallString, cName, cCountry;
    session << "SELECT weatherview_id, city_id "
               "FROM tile "
               "WHERE tile_id = ?",
            into(wId), into(cId), use(id), now;
    session << "SELECT name, description, call_string "
               "FROM weatherview "
               "WHERE weatherview_id = ?",
            into(wName), into(wDescription), into(wCallString),
            use(wId), now;
    session << "SELECT name, country, lon, lat "
               "FROM city "
               "WHERE city_id = ?",
            into(cName), into(cCountry), into(cLon), into(cLat), use(cId), now;
    Weatherview w(wId, wName, wDescription, wCallString);
    City c(cId, cName, cCountry, cLon, cLat);
    Tile t(id, w, c);
    return t;
}

void Database::insertDashboard(Dashboard& d) {
    int dId = d.getId();
    string dName = d.getName();
    if (d.getId() != -1) {
        deleteDashboard(d);
        session << "INSERT INTO dashboard (dashboard_id, name) "
                    "VALUES (?, ?)",
                use(dId), use(dName), now;
    } else {
        session << "INSERT INTO dashboard (name) "
                    "VALUES (?)",
                use(dName), now;
        session << "SELECT last_insert_rowid()", into(dId), now;
    }
    for (Tile t : d.getTiles()) {
        insertTile(t, dId);
    }
}

void Database::deleteDashboard(Dashboard& d) {
    int oldId = d.getId();
    session << "DELETE FROM tile "
                "WHERE dashboard_id = ?",
            use(oldId), now;
    session << "DELETE FROM dashboard "
                "WHERE dashboard_id = ?",
            use(oldId), now;
}

std::vector<Dashboard> Database::getAllDashboards() {
    std::vector<Dashboard> boards;
    Statement select(session);
    select << "SELECT * "
              "FROM dashboard",
            now;
    RecordSet rsd(select);
    for (auto r : rsd) {
        std::vector<Tile> tiles;
        std::vector<int> tIds;
        session << "SELECT tile_id "
                    "FROM tile "
                    "WHERE dashboard_id = ?",
                into(tIds), use(r.get(0)), now;
        for (int id : tIds) {
            Tile t = getTile(id);
            tiles.push_back(t);
        }
        Dashboard d(r.get(0), r.get(1), tiles);
        boards.push_back(d);
    }
    return boards;
}

void Database::clearTables() {
    session << "DELETE FROM tile", now;
    session << "DELETE FROM dashboard", now;
}
