#ifndef OXO_SCREEN_HPP
#define OXO_SCREEN_HPP

#include <SFML/Graphics.hpp>

class Screen {
public :
    // Functions
    virtual int run(sf::RenderWindow &App, int &nbPlayers, std::wstring playersNames[]) = 0;
};

#endif //OXO_SCREEN_HPP
