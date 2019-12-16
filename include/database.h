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
#include "Poco/Data/RecordSet.h"
using namespace std;
using namespace Poco::Data::Keywords;
using namespace Poco::Data;
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
        Weatherview getWeatherview(int);
        void insertTile(Tile&, int);
        Tile getTile(int);
        void clearTables();
        friend int main(int argc, char* argv[]);
    public:
        Database(const string&);
        City getCity(int id);
		void insertCity(City&);
		void deleteCity(int id);
        std::vector<City> getCityByName(string);
        map<int, string> getAllCitiesI();
        map<string, int> getAllCitiesN();
        std::vector<Weatherview> getAllWeatherviews();
        void insertDashboard(Dashboard&);
        Dashboard getDashboard(int);
        void deleteDashboard(Dashboard&);
        std::vector<Dashboard> getAllDashboards();
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
