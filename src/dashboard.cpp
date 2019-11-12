#include "dashboard.h"

Dashboard::Dashboard(std::string name, std::vector<Tile*> tiles)
                : tiles(tiles) {
    this->id = -1;
    this->name = name;
}

Dashboard::Dashboard(int id, std::string name, std::vector<Tile*> tiles)
                : tiles(tiles) {
    this->id = id;
    this->name = name;
}

int Dashboard::getId() const {
    return id;
}

void Dashboard::setId(int id) {
    this->id = id;
}

std::string Dashboard::getName() const {
    return name;
}

void Dashboard::setName(std::string name) {
    this->name = name;
}

std::vector<Tile*> Dashboard::getTiles() const {
    return tiles;
}

void Dashboard::setTiles(std::vector<Tile*> tiles) {
    this->tiles = tiles;
}

