#include <SFML/Graphics.hpp>
#include "model/GlobalConstants.hpp"
#include "model/MLogs.hpp"
#include "view/Screen.hpp"
#include "view/ScreenHomepage.hpp"
#include "view/ScreenSetupGame.hpp"
#include "view/ScreenGame.hpp"
#include "view/ScreenRules.hpp"
#include "view/ScreenCredits.hpp"

int main(int argc, char** argv)
{
    /** CREATING APPLICATION ELEMENTS **/
    std::vector<Screen*> screens;
    int screenActive = 0;

    /** CREATING WINDOW **/
    sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);
    sf::Image icon;
    if (!icon.loadFromFile("src/img/oxo_no_bg.png")){
        createLog("main.cpp : Error loading icon application");
        return (EXIT_FAILURE);
    }
    app.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    /** CREATING SCREENS **/
    ScreenHomepage homepage;
    screens.push_back(&homepage);
    ScreenRules rules;
    screens.push_back(&rules);
    ScreenCredits credits;
    screens.push_back(&credits);
    ScreenSetupGame setupGame;
    screens.push_back(&setupGame);
    ScreenGame game;
    screens.push_back(&game);
    /*Screen index mapping
     * 0: Homepage
     * 1: Rules
     * 2: Credits
     * 3: Game setup
     * 4: Game
     * */

    /** CREATING LOGICAL ELEMENTS **/
    int nbPlayers(0);
    const int Size_playersNames(2);
    std::wstring playersNames[Size_playersNames];

    /** APP LOOP **/
    while (screenActive >= 0) {
        screenActive = screens[screenActive]->run(app, nbPlayers, playersNames);
    }

    if(screenActive == EXIT){
        return EXIT_SUCCESS;
    }else if(screenActive == ERROR){
        return EXIT_FAILURE;
    }
}