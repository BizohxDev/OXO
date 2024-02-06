#ifndef OXO_SCREENSETUPGAME_HPP
#define OXO_SCREENSETUPGAME_HPP

#include "Screen.hpp"

class ScreenSetupGame : public Screen {
private:

public:
    // Constructor
    ScreenSetupGame();

    // Functions
    int run(sf::RenderWindow &app, int &nbPlayers, std::wstring playersNames[]) override;
};


#endif //OXO_SCREENSETUPGAME_HPP
