#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>
#include "tile.h"
using namespace std;

class Dashboard {
    private:
        int id;
        string name;
        vector<Tile*> tiles;
    public:
        Dashboard(string, vector<Tile*>);
        Dashboard(int, string, vector<Tile*>);
        ~Dashboard();
        int getId() const;
        void setId(int);
        string getName() const;
        void setName(string);
        vector<Tile*> getTiles() const;
        void setTiles(vector<Tile*>);
};

#endif //DASHBOARD_H
