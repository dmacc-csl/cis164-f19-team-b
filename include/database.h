#ifndef DATABASE_H
#define DATABASE_h

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <fstream>
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


class FileCheck {
    public:
        FileCheck(const string&);
};

class Database {
    private:
        FileCheck fileCheck;
        string fileName;
        Session session;
    public:
        Database(const string&);
        City getCity(int id);
        map<int, string> getAllCities();
        std::vector<Weatherview> getAllWeatherviews();
};

class DatabaseException: public exception {
    private:
        string eString;
    public:
        DatabaseException(string es) {
            this->eString = es;
        }
        virtual const char* what() const throw() {
            return eString.c_str();
        }
};


#endif // DATABASE_H
