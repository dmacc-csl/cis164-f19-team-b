#include "database.h"

Database::Database(std::string fileName) : fileName(fileName), session("SQLite", fileName) {
}

City Database::getCity(int id) {
    City c(0, "stub", "stub", 0, 0);
    return c;
}








/*
#ifndef DATABASE_H
#define DATABASE_h

#include <iostream>
#include <string>
#include "dashboard.h"
#include "weatherview.h"
#include "city.h"
#include "view.h"

class Database {
    private:
        string fileName;
        Session session;

    public:
        Database(string fileName);
        City getCity(int id);

}

#endif // DATABASE_H
*/
