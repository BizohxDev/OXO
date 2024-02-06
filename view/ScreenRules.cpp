#include "ScreenRules.hpp"
#include <SFML/Audio.hpp>
#include "../model/GlobalConstants.hpp"
#include "MButton.hpp"
#include "../model/MFile.hpp"
#include "../model/MLogs.hpp"

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
ScreenRules::ScreenRules() = default;

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
int ScreenRules::run(sf::RenderWindow &app, int &nbPlayers, std::wstring playersNames[])
{
    /** CREATING SFML ELEMENTS **/
    // Event
    sf::Event event{};

    // Fonts
    sf::Font fontPuffy;
    if (!fontPuffy.loadFromFile("src/font/Puffy.ttf"))
    {
        createLog("ScreenRules.cpp : Error loading Puffy font");
        return (ERROR);
    }
    sf::Font fontFloridaVibes;
    if (!fontFloridaVibes.loadFromFile("src/font/Florida_Vibes.otf"))
    {
        createLog("ScreenRules.cpp : Error loading Florida Vibes font");
        return (ERROR);
    }
    sf::Font fontUbuntuSans;
    if (!fontUbuntuSans.loadFromFile("src/font/UbuntuSans-Regular.ttf"))
    {
        createLog("ScreenRules.cpp : Error loading Ubuntu Sans font");
        return (ERROR);
    }

    // Audio
    sf::SoundBuffer mouseclickBuffer;
    if (!mouseclickBuffer.loadFromFile("src/audio/mouseclick.wav"))
    {
        createLog("ScreenRules.cpp : Error loading mouseclick audio");
        return (ERROR);
    }
    sf::Sound soundMouseclick;
    soundMouseclick.setBuffer(mouseclickBuffer);

    // Background
    sf::RenderTexture bgTexture;
    if (!bgTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT)){
        createLog("ScreenRules.cpp : Error loading background texture");
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
    title.setPosition({((float)WINDOW_WIDTH/2.f)-(title.getGlobalBounds().width/2.f), MAIN_TITLE_POS_Y});

    // Subtitle
    sf::Text subtitle;
    subtitle.setFont(fontUbuntuSans);
    subtitle.setFillColor(SUBTITLE_COLOR);
    subtitle.setCharacterSize(SUBTITLE_SIZE);
    subtitle.setString(L"Règles");
    subtitle.setStyle(SUBTITLE_STYLE);
    subtitle.setPosition(SUBTITLE_POSITION);

    // Rules text
    MFile rulesFiles;
    if (!rulesFiles.readFile("src/text/rules.txt")){
        createLog("ScreenRules.cpp : Error loading rules file");
        return (ERROR);
    }
    sf::Text rulesText;
    rulesText.setFont(fontUbuntuSans);
    rulesText.setFillColor(TEXT_COLOR);
    rulesText.setCharacterSize(TEXT_SIZE);
    rulesText.setString(rulesFiles.getText());
    rulesText.setPosition({subtitle.getPosition().x,  subtitle.getPosition().y + subtitle.getLocalBounds().height + 30.f});
    // Formatting rulesText
    for(int i=0; i<rulesText.getString().getSize(); i++){
        //If the char is out of the window
        if(rulesText.findCharacterPos(i).x > (WINDOW_WIDTH - rulesText.getPosition().x)){
            //Get the last space character in order to make line breaks by word and not by character
            while(rulesText.getString()[i] != ' ')--i;

            //The newline character is added by replacing the space between the two words with \n
            std::wstring str1 = rulesText.getString().toWideString().substr(0,i);
            str1 += L"\n";
            str1 += rulesText.getString().toWideString().substr(i+1);
            rulesText.setString(str1);
        }
    }

    // Back button
    MButton buttonBack(L"> Retour", fontFloridaVibes, BACK_BUTTON_CHAR_SIZE);
    buttonBack.setButtonFillColor(BACK_BUTTON_BG_COLOR);
    buttonBack.setTextFillColor(BACK_BUTTON_TEXT_COLOR);
    buttonBack.setPosition({((float)WINDOW_WIDTH/2.f)-(buttonBack.getButtonSize().x/2.f), BACK_BUTTON_POS_Y});

    /** CREATING LOGICAL ELEMENTS **/
    int selectedPage(-2);

    /** APP LOOP **/
    while (true){
        /** EVENTS LOOP **/
        // Event queue processing
        while (app.pollEvent(event)){
            switch(event.type){
                //Window close request
                case sf::Event::Closed:
                    return(EXIT);
                    break;

                // Mouse
                case sf::Event::MouseMoved:
                    // Back button animation
                    if(buttonBack.isMouseOver(app)){
                        buttonBack.setTextStyle(sf::Text::Style::Underlined);
                    }else{
                        buttonBack.setTextStyle(sf::Text::Style::Regular);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    // Back button action
                    if(buttonBack.isMouseOver(app)){
                        selectedPage = 0; // Go to home page
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
        app.clear();
        app.draw(bgSprite);
        app.draw(title);
        app.draw(subtitle);
        app.draw(rulesText);
        app.draw(buttonBack);
        app.display();
    }

    //Never reaching this point normally, but just in case, exit the application
    return (ERROR);
}