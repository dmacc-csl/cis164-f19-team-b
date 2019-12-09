#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "Bank.h"

class WebServer {
private:
    Bank *bank;
public:
    string drawTile(Tile&, int);
};

#endif // WEB_SERVER_H
