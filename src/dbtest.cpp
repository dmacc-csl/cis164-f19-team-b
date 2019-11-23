#include <iostream>
#include "database.h"
using namespace std;

int main(int argc, char* argv[]) {
    string dbfile = "dashboards.db";
    if (argc > 1) {
        dbfile = argv[1];
    }
    Poco::Data::SQLite::Connector::registerConnector();


    Database database(dbfile);

    City c = database.getCity(707860);

    cout << c.getName() << endl;
}
