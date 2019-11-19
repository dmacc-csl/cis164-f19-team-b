#include "city.h"

City::City(int id, std::string name, std::string country,
            double lon, double lat) {
    this->id = id;
    this->name = name;
    this->country = country;
    this->lon = lon;
    this->lat = lat;
}

int City::getId() const {
    return id;
}

std::string City::getName() const {
    return name;
}

std::string City::getCountry() const {
    return country;
}

double City::getLon() const {
    return lon;
}

double City::getLat() const {
    return lat;
}

bool City::operator==(const City& c) const {
        return (this->id == c.getId());
}

size_t CityHashId::operator()(const City& c) const
{
    return c.getId();
}

