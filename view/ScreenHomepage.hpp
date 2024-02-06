#ifndef OXO_SCREENMENU_HPP
#define OXO_SCREENMENU_HPP

#include "Screen.hpp"

class ScreenHomepage : public Screen {
private:

public:
    // Constructor
    ScreenHomepage();

    // Functions
    int run(sf::RenderWindow &App, int &nbPlayers, std::wstring playersNames[]) override;
};

#endif //OXO_SCREENMENU_HPP
