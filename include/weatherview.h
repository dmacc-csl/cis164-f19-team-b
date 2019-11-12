#ifndef WEATHERVIEW_H
#define WEATHERVIEW_H

#include <string>

class Weatherview {
    private:
        int id;
        std::string name;
        std::string description;
        std::string callString;
    public:
        Weatherview(int, std::string, std::string, std::string);
        int getId() const;
        std::string getName() const;
        std::string getDescription() const;
        std::string getCallString() const;
};

#endif //WEATHERVIEW_H

