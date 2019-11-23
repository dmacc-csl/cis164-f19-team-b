#include "database.h"

Database::Database(string fileName) : fileName(fileName), session("SQLite", fileName) {
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
    return map<int, string>();
}




