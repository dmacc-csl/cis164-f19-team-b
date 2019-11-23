#ifndef DATABASE_H
#define DATABASE_h

#include <iostream>
#include <string>
#include "dashboard.h"
#include "weatherview.h"
#include "city.h"
#include "weatherview.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;


class Database {
    private:
        std::string fileName;
        Session session;

    public:
        Database(std::string);
        City getCity(int id);

};

#endif // DATABASE_H
