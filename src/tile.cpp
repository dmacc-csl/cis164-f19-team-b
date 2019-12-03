#include "tile.h"

Tile::Tile(Weatherview& weatherview, City& city)
            : weatherview(weatherview), city(city) {
    this->id = -1;
}

Tile::Tile(int id, Weatherview& weatherview, City& city)
            : weatherview(weatherview), city(city) {
    this->id = id;
}

Tile::~Tile() {
    delete &weatherview;
    delete &city;
}

int Tile::getId() const {
    return id;
}

void Tile::setId(int id) {
    this->id = id;
}

Weatherview& Tile::getWeatherview() const {
    return weatherview;
}

void Tile::setWeatherview(Weatherview& weatherview) {
    this->weatherview = weatherview;
}

City& Tile::getCity() const {
    return city;
}

void Tile::setCity(City& city) {
    this->city = city;
}

