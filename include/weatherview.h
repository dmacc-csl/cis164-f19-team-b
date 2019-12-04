#ifndef WEATHERVIEW_H
#define WEATHERVIEW_H

#include <string>
using namespace std;

class Weatherview {
    private:
        int id;
        string name;
        string description;
        string callString;
    public:
        Weatherview(int, string, string, string);
        int getId() const;
        string getName() const;
        string getDescription() const;
        string getCallString() const;
};

#endif //WEATHERVIEW_H

