#include "dashboard.h"

Dashboard::Dashboard(string name, vector<Tile*> tiles)
                : tiles(tiles) {
    this->id = -1;
    this->name = name;
}

Dashboard::Dashboard(int id, string name, vector<Tile*> tiles)
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

string Dashboard::getName() const {
    return name;
}

void Dashboard::setName(string name) {
    this->name = name;
}

vector<Tile*> Dashboard::getTiles() const {
    return tiles;
}

void Dashboard::setTiles(vector<Tile*> tiles) {
    this->tiles = tiles;
}

