#ifndef CITY_H
#define CITY_H

#include <string>
using namespace std;

class City {
    private:
        int id;
        string name;
        string country;
        double lon, lat;
    public:
        City(int, string, string, double, double);
        int getId() const;
        string getName() const;
        string getCountry() const;
        double getLon() const;
        double getLat() const;

        bool operator==(const City&) const;
};

class CityHashId {
    public:
        // id is returned as hash function
        size_t operator()(const City&) const;
};

#endif //CITY_H

