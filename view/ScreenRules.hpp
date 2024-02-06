#ifndef OXO_SCREENRULES_HPP
#define OXO_SCREENRULES_HPP

#include "Screen.hpp"

class ScreenRules : public Screen {
private:

public:
    // Constructor
    ScreenRules();

    // Functions
    int run(sf::RenderWindow &app, int &nbPlayers, std::wstring playersNames[]) override;
};


#endif //OXO_SCREENRULES_HPP
