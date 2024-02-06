#ifndef OXO_SCREENCREDITS_HPP
#define OXO_SCREENCREDITS_HPP

#include "Screen.hpp"

class ScreenCredits : public Screen {
private:

public:
    // Constructor
    ScreenCredits();

    // Functions
    int run(sf::RenderWindow &app, int &nbPlayers, std::wstring playersNames[]) override;
};


#endif //OXO_SCREENCREDITS_HPP
