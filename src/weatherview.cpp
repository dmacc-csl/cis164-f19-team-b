#include "weatherview.h"

Weatherview::Weatherview(int id, std::string name, std::string description,
        std::string callString) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->callString = callString;
}

int Weatherview::getId() const {
    return id;
}

std::string Weatherview::getName() const {
    return name;
}

std::string Weatherview::getDescription() const {
    return description;
}

std::string Weatherview::getCallString() const {
    return callString;
}

