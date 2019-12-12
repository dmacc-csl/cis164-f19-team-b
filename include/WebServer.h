#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "database.h"
#include <string>
#include <map>

using namespace std;

class WebServer {
private:

public:
    std::string drawTile(Tile&, int);
};

#endif // WEB_SERVER_H
