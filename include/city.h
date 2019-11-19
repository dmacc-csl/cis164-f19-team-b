#ifndef CITY_H
#define CITY_H

#include <string>

class City {
    private:
        int id;
        std::string name;
        std::string country;
        double lon, lat;
    public:
        City(int, std::string, std::string, double, double);
        int getId() const;
        std::string getName() const;
        std::string getCountry() const;
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

