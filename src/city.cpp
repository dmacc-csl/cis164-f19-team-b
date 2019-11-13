#include "city.h"

City::City(int id, std::string name, std::string country, Coord coord) {
    this->id = id;
    this->name = name;
    this->country = country;
    this->coord = coord;
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

