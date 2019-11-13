#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>
#include "tile.h"

class Dashboard {
    private:
        int id;
        std::string name;
        std::vector<Tile*> tiles;
    public:
        Dashboard(std::string, std::vector<Tile*>);
        Dashboard(int, std::string, std::vector<Tile*>);
        int getId() const;
        void setId(int);
        std::string getName() const;
        void setName(std::string);
        std::vector<Tile*> getTiles() const;
        void setTiles(std::vector<Tile*>);
};

#endif //DASHBOARD_H
