#include "ScreenGame.hpp"
#include <SFML/Audio.hpp>
#include "../model/GlobalConstants.hpp"
#include "MButton.hpp"
#include "../controller/Game.hpp"
#include "../model/MLogs.hpp"

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
ScreenGame::ScreenGame() = default;

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
int ScreenGame::run(sf::RenderWindow &app, int &nbPlayers, std::wstring playersNames[])
{
    /** CREATING SFML ELEMENTS **/
    // Event
    sf::Event event{};

    // Fonts
    sf::Font fontPuffy;
    if (!fontPuffy.loadFromFile("src/font/Puffy.ttf"))
    {
        createLog("ScreenGame.cpp : Error loading Puffy font");
        return (ERROR);
    }
    sf::Font fontFloridaVibes;
    if (!fontFloridaVibes.loadFromFile("src/font/Florida_Vibes.otf"))
    {
        createLog("ScreenGame.cpp : Error loading Florida Vibes font");
        return (ERROR);
    }
    sf::Font fontUbuntuSans;
    if (!fontUbuntuSans.loadFromFile("src/font/UbuntuSans-Regular.ttf"))
    {
        createLog("ScreenGame.cpp : Error loading Ubuntu Sans font");
        return (ERROR);
    }

    // Audio
    sf::SoundBuffer mouseclickBuffer;
    if (!mouseclickBuffer.loadFromFile("src/audio/mouseclick.wav"))
    {
        createLog("ScreenGame.cpp : Error loading mouseclick audio");
        return (ERROR);
    }
    sf::Sound soundMouseclick;
    soundMouseclick.setBuffer(mouseclickBuffer);
    sf::SoundBuffer playBuffer;
    if (!playBuffer.loadFromFile("src/audio/play.wav"))
    {
        createLog("ScreenGame.cpp : Error loading play audio");
        return (ERROR);
    }
    sf::Sound soundPlay;
    soundPlay.setBuffer(playBuffer);
    sf::SoundBuffer winBuffer;
    if (!winBuffer.loadFromFile("src/audio/win.wav"))
    {
        createLog("ScreenGame.cpp : Error loading win audio");
        return (ERROR);
    }
    sf::Sound soundWin;
    soundWin.setBuffer(winBuffer);
    sf::SoundBuffer drawBuffer;
    if (!drawBuffer.loadFromFile("src/audio/draw.wav"))
    {
        createLog("ScreenGame.cpp : Error loading draw audio");
        return (ERROR);
    }
    sf::Sound soundDraw;
    soundDraw.setBuffer(drawBuffer);

    // Background
    sf::RenderTexture bgTexture;
    if (!bgTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT)){
        createLog("ScreenGame.cpp : Error loading background texture");
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

    // Game instructions
    sf::Text gameInstructions;
    gameInstructions.setFont(fontUbuntuSans);
    gameInstructions.setFillColor(TEXT_COLOR);
    gameInstructions.setCharacterSize(25.f);
    gameInstructions.setString(L"C'est à " + playersNames[0] + L" de jouer");
    gameInstructions.setPosition({((float)WINDOW_WIDTH/2) - (gameInstructions.getLocalBounds().width/2), SUBTITLE_POSITION.y});

    // GAME GRID
    const float gridSize(246.f);
    const sf::Vector2f gridPosition({((float)WINDOW_WIDTH/2.f) - (gridSize/2.f), 155.f});
    const float cellSize(80.f);
    const float lineThickness(3.f);
    // Lines
    sf::RectangleShape lineH1(sf::Vector2f(lineThickness, gridSize));
    sf::RectangleShape lineH2(sf::Vector2f(lineThickness, gridSize));
    sf::RectangleShape lineV1(sf::Vector2f(gridSize, lineThickness));
    sf::RectangleShape lineV2(sf::Vector2f(gridSize, lineThickness));
    lineH1.setPosition(gridPosition.x + cellSize, gridPosition.y);
    lineH2.setPosition(gridPosition.x + cellSize*2 + lineThickness, gridPosition.y);
    lineV1.setPosition(gridPosition.x, gridPosition.y + cellSize);
    lineV2.setPosition(gridPosition.x, gridPosition.y + cellSize*2 + lineThickness);
    lineH1.setFillColor(sf::Color::Black);
    lineH2.setFillColor(sf::Color::Black);
    lineV1.setFillColor(sf::Color::Black);
    lineV2.setFillColor(sf::Color::Black);
    // Grid (buttons)
    MButton grid[3][3];
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            grid[r][c].create(L" ", fontUbuntuSans, GRID_BUTTON_CHAR_SIZE);
            grid[r][c].setButtonFillColor(GRID_BUTTON_BG_COLOR);
            grid[r][c].setTextFillColor(GRID_BUTTON_TEXT_COLOR);
            grid[r][c].setButtonSize({cellSize, cellSize});
            grid[r][c].setPosition({gridPosition.x + (float)r * (cellSize+lineThickness), gridPosition.y + (float)c * (cellSize + lineThickness)});
            grid[r][c].setButtonOutlineThickness(-1.f);
            grid[r][c].setButtonOutlineColor(sf::Color::Transparent);
        }
    }

    // Back button
    MButton buttonBack(L"> Quitter la partie", fontFloridaVibes, BACK_BUTTON_CHAR_SIZE);
    buttonBack.setButtonFillColor(BACK_BUTTON_BG_COLOR);
    buttonBack.setTextFillColor(BACK_BUTTON_TEXT_COLOR);
    buttonBack.setPosition({((float)WINDOW_WIDTH/2.f)-(buttonBack.getButtonSize().x/2.f), BACK_BUTTON_POS_Y});

    /** CREATING LOGICAL ELEMENTS **/
    int selectedPage(-2);
    Game game;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            grid[r][c].setText(game.getCellInWstring(r, c));
            grid[r][c].setPosition({gridPosition.x + (float)r * (cellSize+lineThickness), gridPosition.y + (float)c * (cellSize+lineThickness)});
        }
    }
    bool endGame(false);

    /** APP LOOP **/
    while (true){
        // IA play
        if((game.getNbRounds() % 2) && (nbPlayers == 1) && !endGame){
            game.autoPlay('O');
            soundPlay.play();
            gameInstructions.setString(L"C'est à " + playersNames[0] + L" de jouer");
            gameInstructions.setPosition({((float)WINDOW_WIDTH/2) - (gameInstructions.getLocalBounds().width/2), SUBTITLE_POSITION.y});
        }

        /** EVENTS LOOP **/
        // Event queue processing
        while (app.pollEvent(event)){
            switch(event.type){
                // Window close request
                case sf::Event::Closed:
                    return(EXIT);
                    break;

                // Mouse
                case sf::Event::MouseMoved:
                    // Grid animation
                    for (int r = 0; r < 3; r++) {
                        for (int c = 0; c < 3; c++) {
                            if(grid[r][c].isMouseOver(app) && !game.isCellPlayed(r, c)){
                                grid[r][c].setButtonOutlineColor(sf::Color::White);
                            }else{
                                grid[r][c].setButtonOutlineColor(sf::Color::Transparent);
                            }
                        }
                    }
                    // Back button animation
                    if(buttonBack.isMouseOver(app)){
                        buttonBack.setTextStyle(sf::Text::Style::Underlined);
                    }else{
                        buttonBack.setTextStyle(sf::Text::Style::Regular);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    // Grid action
                    for (int r = 0; r < 3; r++) {
                        for (int c = 0; c < 3; c++) {
                            if(grid[r][c].isMouseOver(app) && !game.isCellPlayed(r, c)){
                                if((game.getNbRounds() % 2) && (nbPlayers == 2)){
                                    game.playCell(r, c, 'O');
                                    soundPlay.play();
                                    gameInstructions.setString(L"C'est à " + playersNames[0] + L" de jouer");
                                    gameInstructions.setPosition({((float)WINDOW_WIDTH/2) - (gameInstructions.getLocalBounds().width/2), SUBTITLE_POSITION.y});
                                }else if(!(game.getNbRounds() % 2)){
                                    game.playCell(r, c, 'X');
                                    soundPlay.play();
                                    gameInstructions.setString(L"C'est à " + playersNames[1] + L" de jouer");
                                    gameInstructions.setPosition({((float)WINDOW_WIDTH/2) - (gameInstructions.getLocalBounds().width/2), SUBTITLE_POSITION.y});
                                }
                                grid[r][c].setButtonOutlineColor(sf::Color::Transparent);
                            }
                        }
                    }

                    // Back button action
                    if(buttonBack.isMouseOver(app)){
                        selectedPage = 0; // Go to home page
                        soundMouseclick.play();
                    }
                    break;

                // Nothing
                default:
                    break;
            }
        }
        /** UPDATE LOGIC **/
        // Go to another page
        if((soundMouseclick.getStatus() != sf::SoundSource::Playing) && (selectedPage > -2)){
            return selectedPage;
        }
        //if(soundPlay.getStatus() != sf::SoundSource::Playing)
        // Check victory of 'X' player
        if(game.checkVictory('X') && !endGame){
            soundWin.play();
            gameInstructions.setString(playersNames[0] + L" a gagné la partie !");
            gameInstructions.setPosition({((float)WINDOW_WIDTH/2) - (gameInstructions.getLocalBounds().width/2), SUBTITLE_POSITION.y});
            game.setAllCellsPlayed(true);
            endGame = true;
        }
        // Check victory of 'O' player
        if(game.checkVictory('O') && !endGame){
            soundWin.play();
            gameInstructions.setString(playersNames[1] + L" a gagné la partie !");
            gameInstructions.setPosition({((float)WINDOW_WIDTH/2) - (gameInstructions.getLocalBounds().width/2), SUBTITLE_POSITION.y});
            game.setAllCellsPlayed(true);
            endGame = true;
        }
        // Draw
        if((game.getNbRounds() == 9) && !endGame){
            soundDraw.play();
            gameInstructions.setString(L"Match nul !");
            gameInstructions.setPosition({((float)WINDOW_WIDTH/2) - (gameInstructions.getLocalBounds().width/2), SUBTITLE_POSITION.y});
            endGame = true;
        }


        /** UPDATE SCREEN **/
        //Update screen
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                grid[r][c].setText(game.getCellInWstring(r, c));
                grid[r][c].setPosition({gridPosition.x + (float)r * (cellSize+lineThickness), gridPosition.y + (float)c * (cellSize+lineThickness)});
            }
        }

        /** DISPLAY SCREEN **/
        app.clear();
        app.draw(bgSprite);
        app.draw(title);
        app.draw(gameInstructions);
        app.draw(lineH1);
        app.draw(lineH2);
        app.draw(lineV1);
        app.draw(lineV2);
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                app.draw(grid[r][c]);
            }
        }
        app.draw(buttonBack);
        app.display();
    }

    //Never reaching this point normally, but just in case, exit the application
    return (ERROR);
}