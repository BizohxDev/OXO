#include "ScreenSetupGame.hpp"
#include <SFML/Audio.hpp>
#include "../model/GlobalConstants.hpp"
#include "MButton.hpp"
#include "MTextbox.hpp"
#include "../model/MLogs.hpp"

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
ScreenSetupGame::ScreenSetupGame() = default;

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
int ScreenSetupGame::run(sf::RenderWindow &app, int &nbPlayers, std::wstring playersNames[])
{
    /** CREATING SFML ELEMENTS **/
    // Event
    sf::Event event{};

    // Fonts
    sf::Font fontPuffy;
    if (!fontPuffy.loadFromFile("src/font/Puffy.ttf"))
    {
        createLog("ScreenSetupGame.cpp : Error loading Puffy font");
        return (ERROR);
    }
    sf::Font fontFloridaVibes;
    if (!fontFloridaVibes.loadFromFile("src/font/Florida_Vibes.otf"))
    {
        createLog("ScreenSetupGame.cpp : Error loading Florida Vibes font");
        return (ERROR);
    }
    sf::Font fontUbuntuSans;
    if (!fontUbuntuSans.loadFromFile("src/font/UbuntuSans-Regular.ttf"))
    {
        createLog("ScreenSetupGame.cpp : Error loading Ubuntu Sans font");
        return (ERROR);
    }

    // Audio
    sf::SoundBuffer mouseclickBuffer;
    if (!mouseclickBuffer.loadFromFile("src/audio/mouseclick.wav"))
    {
        createLog("ScreenSetupGame.cpp : Error loading mouseclick audio");
        return (ERROR);
    }
    sf::Sound soundMouseclick;
    soundMouseclick.setBuffer(mouseclickBuffer);

    // Background
    sf::RenderTexture bgTexture;
    if (!bgTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT)){
        createLog("ScreenSetupGame.cpp : Error loading background texture");
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
    subtitle.setString(L"Paramètres de la partie");
    subtitle.setStyle(SUBTITLE_STYLE);
    subtitle.setPosition(SUBTITLE_POSITION);

    // Text for selecting the number of players
    sf::Text textNbPlayer;
    textNbPlayer.setFont(fontUbuntuSans);
    textNbPlayer.setFillColor(TEXT_COLOR);
    textNbPlayer.setCharacterSize(TEXT_SIZE);
    textNbPlayer.setString(L"Choix du nombre de joueurs :");
    textNbPlayer.setPosition({subtitle.getPosition().x, subtitle.getPosition().y + subtitle.getLocalBounds().height + 30.f});

    // Buttons for selecting the number of players
    const int Size_nbPlayerButtons(2);
    MButton nbPlayerButtons[Size_nbPlayerButtons];
    nbPlayerButtons[0].create(L"1 Joueur", fontUbuntuSans, TEXT_SIZE);
    nbPlayerButtons[1].create(L"2 Joueurs", fontUbuntuSans, TEXT_SIZE);
    for (auto &button : nbPlayerButtons) {
        button.setButtonFillColor(sf::Color::White);
        button.setButtonOutlineThickness(1.f);
        button.setButtonOutlineColor(sf::Color::Black);
        button.setTextFillColor(sf::Color::Black);
        button.setButtonSize({110.f, 40.f});
    }
    nbPlayerButtons[0].setPosition({((float)WINDOW_WIDTH/2.f) - nbPlayerButtons[0].getButtonSize().x - 50.f, textNbPlayer.getPosition().y + textNbPlayer.getLocalBounds().height + 15.f});
    nbPlayerButtons[1].setPosition({((float)WINDOW_WIDTH/2.f) + 50.f, textNbPlayer.getPosition().y + textNbPlayer.getLocalBounds().height + 15.f});

    // Text for choose the names of players
    const int Size_textNamePlayer(2);
    sf::Text textNamePlayer[Size_textNamePlayer];
    textNamePlayer[0].setString(L"Nom du joueur n°1 : ");
    textNamePlayer[1].setString(L"Nom du joueur n°2 : ");
    for (int i = 0; i < Size_textNamePlayer; ++i) {
        textNamePlayer[i].setFont(fontUbuntuSans);
        textNamePlayer[i].setFillColor(TEXT_COLOR);
        textNamePlayer[i].setCharacterSize(TEXT_SIZE);
        textNamePlayer[i].setPosition({subtitle.getPosition().x, ((float)i*40.f) + nbPlayerButtons[0].getPosition().y + nbPlayerButtons[0].getButtonSize().y + 30.f});
    }

    // Textboxes for choose the names of players
    const int Size_namePlayerTextboxes(2);
    MTextbox namePlayerTextboxes[Size_namePlayerTextboxes];
    for (int i = 0; i < Size_namePlayerTextboxes; ++i) {
        namePlayerTextboxes[i].create(fontUbuntuSans, TEXT_SIZE, false);
        namePlayerTextboxes[i].setTextboxOutlineThickness(1.f);
        namePlayerTextboxes[i].setTextboxOutlineColor(sf::Color::Black);
        namePlayerTextboxes[i].setTextFillColor(sf::Color::Black);
        namePlayerTextboxes[i].setTextboxSize({290.f, 32.f});
        namePlayerTextboxes[i].setLimit(true, 15);
        namePlayerTextboxes[i].setPosition({textNamePlayer[i].getPosition().x + 200.f, (textNamePlayer[i].getPosition().y - 4.f)});
    }

    // Back button
    MButton buttonBack(L"> Retour", fontFloridaVibes, BACK_BUTTON_CHAR_SIZE);
    buttonBack.setButtonFillColor(BACK_BUTTON_BG_COLOR);
    buttonBack.setTextFillColor(BACK_BUTTON_TEXT_COLOR);
    buttonBack.setPosition({((float)WINDOW_WIDTH/2.f)-(buttonBack.getButtonSize().x/2.f), BACK_BUTTON_POS_Y});

    // Start game button
    MButton buttonStartGame(L"> Lancer la partie !", fontFloridaVibes, 48);
    buttonStartGame.setButtonFillColor(sf::Color::Transparent);
    buttonStartGame.setTextFillColor(sf::Color::Black);
    buttonStartGame.setPosition({((float)WINDOW_WIDTH/2.f)-(buttonStartGame.getButtonSize().x/2.f), (float)WINDOW_HEIGHT - buttonBack.getButtonSize().y - buttonStartGame.getButtonSize().y - 40.f});

    /** CREATING LOGICAL ELEMENTS **/
    int selectedPage(-2);
    int choiceNbPlayer(0);
    bool ready(false);

    /** APP LOOP **/
    while (true){
        /** EVENTS LOOP **/
        // Event queue processing
        while (app.pollEvent(event)){
            switch(event.type){
                // Window close request
                case sf::Event::Closed:
                    return(EXIT);
                    break;

                // Text
                case sf::Event::TextEntered:
                    for (auto &textbox : namePlayerTextboxes) {
                        textbox.typedOn(event);
                    }
                    break;

                // Mouse
                case sf::Event::MouseMoved:
                    // Start game button animation
                    if(buttonStartGame.isMouseOver(app)){
                        buttonStartGame.setTextStyle(sf::Text::Style::Underlined);
                    }else{
                        buttonStartGame.setTextStyle(sf::Text::Style::Regular);
                    }

                    // Back button animation
                    if(buttonBack.isMouseOver(app)){
                        buttonBack.setTextStyle(sf::Text::Style::Underlined);
                    }else{
                        buttonBack.setTextStyle(sf::Text::Style::Regular);
                    }

                    // Selecting the number of players button animation
                    for (auto &button : nbPlayerButtons) {
                        if(button.isMouseOver(app)){
                            button.setButtonOutlineColor(sf::Color::Blue);
                        }else{
                            button.setButtonOutlineColor(sf::Color::Black);
                        }
                    }

                    // Selecting the name of players textboxes animation
                    for (auto &textbox : namePlayerTextboxes) {
                        if(textbox.isMouseOver(app)){
                            textbox.setTextboxOutlineColor(sf::Color::Blue);
                        }else{
                            textbox.setTextboxOutlineColor(sf::Color::Black);
                        }
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    // Selecting the number of players button action
                    for (int i = 0; i < Size_nbPlayerButtons; ++i) {
                        if(nbPlayerButtons[i].isMouseOver(app)){
                            choiceNbPlayer = i + 1;
                        }
                    }

                    // Selecting the name of players textboxes action
                    for (auto &textbox : namePlayerTextboxes) {
                        if(textbox.isMouseOver(app)){
                            textbox.setSelected(true);
                        }else{
                            textbox.setSelected(false);
                        }
                    }

                    // Start game button action
                    if(buttonStartGame.isMouseOver(app) && ready){
                        nbPlayers = choiceNbPlayer;
                        playersNames[0] = namePlayerTextboxes[0].getTextWstring();
                        if(choiceNbPlayer == 2){
                            playersNames[1] = namePlayerTextboxes[1].getTextWstring();
                        }else{
                            playersNames[1] = L"l'IA";
                        }
                        selectedPage = 4; // Go to game page
                        soundMouseclick.play();
                    }

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
        // Check if needed information is provided to get ready to play
        if(choiceNbPlayer == 1 && !namePlayerTextboxes[0].getText().empty()){
            ready = true;
        }else if(choiceNbPlayer == 2 && !namePlayerTextboxes[0].getText().empty() && !namePlayerTextboxes[1].getText().empty()){
            ready = true;
        }else{
            ready = false;
        }

        /** UPDATE SCREEN **/
        // Set background color for selected button (choice of number of players)
        for (auto &button : nbPlayerButtons) {
            button.setButtonFillColor(sf::Color::White);
        }
        if(choiceNbPlayer > 0){
            nbPlayerButtons[choiceNbPlayer-1].setButtonFillColor(M_COLOR_BLUE_TRANSPARENT);
        }

        // Set outline color for selected textbox
        for (auto &textbox : namePlayerTextboxes) {
            if(textbox.isSelected()){
                textbox.setTextboxOutlineColor(sf::Color::Blue);
            }
        }
        // Blinks the cursor of the selected textbox
        for (auto &textbox : namePlayerTextboxes) {
            textbox.updateCursor();
        }

        /** DISPLAY SCREEN **/
        app.clear();
        app.draw(bgSprite);
        app.draw(title);
        app.draw(subtitle);
        app.draw(textNbPlayer);
        for (const auto & nbPlayerButton : nbPlayerButtons) {
            app.draw(nbPlayerButton);
        }
        for (int i = 0; i < choiceNbPlayer; ++i) {
            app.draw(textNamePlayer[i]);
            app.draw(namePlayerTextboxes[i]);
        }
        app.draw(buttonStartGame);
        app.draw(buttonBack);
        app.display();
    }

    //Never reaching this point normally, but just in case, exit the application
    return (ERROR);
}