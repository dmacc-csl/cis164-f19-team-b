#ifndef CITY_H
#define CITY_H

#include <string>

struct Coord {
    double lon, lat;
};

class City {
    private:
        int id;
        std::string name;
        std::string country;
        Coord coord;
    public:
        City(int, std::string, std::string, Coord);
        int getId() const;
        std::string getName() const;
        std::string getCountry() const;
        Coord getCoord() const;

};

#endif //CITY_H

