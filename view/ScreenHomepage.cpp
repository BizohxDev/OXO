#include "ScreenHomepage.hpp"
#include <SFML/Audio.hpp>
#include "../model/GlobalConstants.hpp"
#include "MButton.hpp"
#include "../model/MLogs.hpp"

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
ScreenHomepage::ScreenHomepage() = default;

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
int ScreenHomepage::run(sf::RenderWindow &App, int &nbPlayers, std::wstring playersNames[])
{
    /** CREATING SFML ELEMENTS **/
    // Event
    sf::Event event{};

    // Fonts
    sf::Font fontPuffy;
    if (!fontPuffy.loadFromFile("src/font/Puffy.ttf"))
    {
        createLog("ScreenHomepage.cpp : Error loading Puffy font");
        return (ERROR);
    }
    sf::Font fontFloridaVibes;
    if (!fontFloridaVibes.loadFromFile("src/font/Florida_Vibes.otf"))
    {
        createLog("ScreenHomepage.cpp : Error loading Florida Vibes font");
        return (ERROR);
    }
    sf::Font fontUbuntuSans;
    if (!fontUbuntuSans.loadFromFile("src/font/UbuntuSans-Regular.ttf"))
    {
        createLog("ScreenHomepage.cpp : Error loading Ubuntu Sans font");
        return (ERROR);
    }

    // Audio
    sf::SoundBuffer mouseclickBuffer;
    if (!mouseclickBuffer.loadFromFile("src/audio/mouseclick.wav"))
    {
        createLog("ScreenHomepage.cpp : Error loading mouseclick audio");
        return (ERROR);
    }
    sf::Sound soundMouseclick;
    soundMouseclick.setBuffer(mouseclickBuffer);

    // Background
    sf::RenderTexture bgTexture;
    if (!bgTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT)){
        createLog("ScreenHomepage.cpp : Error loading background texture");
        return (ERROR);
    }
    bgTexture.clear(BACKGROUND_COLOR);
    sf::Sprite bgSprite(bgTexture.getTexture());

    // Main title
    sf::Text title;
    title.setFont(fontPuffy);
    title.setFillColor(MAIN_TITLE_COLOR);
    title.setCharacterSize(MAIN_TITLE_SIZE);
    title.setString(MAIN_TITLE_TEXT);
    title.setPosition({((float)WINDOW_WIDTH/2)-(title.getGlobalBounds().width/2), MAIN_TITLE_POS_Y});

    // Menu buttons
    const int Size_menuButtons(4);
    MButton menuButtons[Size_menuButtons];
    menuButtons[0].create(L"> Jouer", fontFloridaVibes, 48);
    menuButtons[1].create(L"> Règles", fontFloridaVibes, 48);
    menuButtons[2].create(L"> Crédits", fontFloridaVibes, 48);
    menuButtons[3].create(L"> Quitter", fontFloridaVibes, 48);
    for(int i = 0; i < Size_menuButtons; ++i) {
        menuButtons[i].setButtonFillColor(sf::Color::Transparent);
        menuButtons[i].setTextFillColor(sf::Color::Black);
        menuButtons[i].setButtonSize({150.f, 50.f});
        menuButtons[i].setPosition({50.f, ((float)i*70.f) + 140.f});
    }

    // Illustration
    sf::Texture illusTexture;
    if (!illusTexture.loadFromFile("src/img/illustration.png")) {
        createLog("ScreenHomepage.cpp : Error loading illustration");
        return (ERROR);
    }
    sf::Sprite illusSprite(illusTexture);
    illusSprite.setPosition({(((float)WINDOW_WIDTH + 200.f)/2.f) - (illusSprite.getLocalBounds().width/2.f), ((float)WINDOW_HEIGHT/2.f)-(illusSprite.getLocalBounds().height/2.f) + 25.f});

    /** CREATING LOGICAL ELEMENTS **/
    int selectedPage(-2);

    /** APP LOOP **/
    while (true){
        /** EVENTS LOOP **/
        // Event queue processing
        while (App.pollEvent(event)){
            switch(event.type){
                // Window close request
                case sf::Event::Closed:
                    return(EXIT);
                    break;

                // Mouse
                case sf::Event::MouseMoved:
                    // Menu button animation
                    for (auto &button : menuButtons) {
                        if(button.isMouseOver(App)){
                            button.setTextStyle(sf::Text::Style::Underlined);
                        }else{
                            button.setTextStyle(sf::Text::Style::Regular);
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    // Menu button action
                    if(menuButtons[0].isMouseOver(App)){
                        selectedPage = 3; // Go to setup game page
                        soundMouseclick.play();
                    }
                    if(menuButtons[1].isMouseOver(App)){
                        selectedPage = 1; // Go to rules page
                        soundMouseclick.play();
                    }
                    if(menuButtons[2].isMouseOver(App)){
                        selectedPage = 2; // Go to credits page
                        soundMouseclick.play();
                    }
                    if(menuButtons[3].isMouseOver(App)){
                        selectedPage = EXIT; // Exit application
                        soundMouseclick.play();
                    }
                    break;

                    //Nothing
                default:
                    break;
            }
        }
        /** UPDATE LOGIC **/
        // Go to another page
        if((soundMouseclick.getStatus() != sf::SoundSource::Playing) && (selectedPage > -2)){
            return selectedPage;
        }

        /** UPDATE SCREEN **/
        // (none)

        /** DISPLAY SCREEN **/
        App.clear();
        App.draw(bgSprite);
        App.draw(title);
        for (const auto &button : menuButtons) {
            App.draw(button);
        }
        App.draw(illusSprite);
        App.display();
    }

    //Never reaching this point normally, but just in case, exit the application
    return (ERROR);
}