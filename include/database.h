#ifndef DATABASE_H
#define DATABASE_h

#include <iostream>
#include <string>
#include <map>
#include "dashboard.h"
#include "weatherview.h"
#include "city.h"
#include "weatherview.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
using namespace std;
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;



class Database {
    private:
        string fileName;
        Session session;

    public:
        Database(string);
        City getCity(int id);
        map<int, string> getAllCities();

};

#endif // DATABASE_H
