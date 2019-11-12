#ifndef TILE_H
#define TILE_H

#include "weatherview.h"
#include "city.h"

class Tile {
    private:
        int id;
        Weatherview& weatherview;
        City& city;
    public:
        Tile(Weatherview&, City&);
        Tile(int, Weatherview&, City&);
        int getId () const;
        void setId(int);
        Weatherview& getWeatherview() const;
        void setWeatherview(Weatherview&);
        City& getCity() const;
        void setCity(City&);
};

#endif //TILE_H

