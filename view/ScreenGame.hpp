#ifndef OXO_SCREENGAME_HPP
#define OXO_SCREENGAME_HPP

#include "Screen.hpp"

class ScreenGame : public Screen {
private:

public:
    // Constructor
    ScreenGame();

    // Functions
    int run(sf::RenderWindow &app, int &nbPlayers, std::wstring playersNames[]) override;
};

#endif //OXO_SCREENGAME_HPP
