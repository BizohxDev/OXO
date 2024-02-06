#ifndef OXO_GLOBALCONSTANTS_HPP
#define OXO_GLOBALCONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <string>

#define EXIT -1
#define ERROR -2

const unsigned int WINDOW_WIDTH(640);
const unsigned int WINDOW_HEIGHT(480);
const std::wstring WINDOW_TITLE(L"OXO");
const sf::Color BACKGROUND_COLOR(212, 198, 170);

const std::wstring MAIN_TITLE_TEXT(L"OXO");
const unsigned int MAIN_TITLE_SIZE(80);
const sf::Color MAIN_TITLE_COLOR(sf::Color(201, 30, 30, 255));
const float MAIN_TITLE_POS_Y(5.f);

const unsigned int SUBTITLE_SIZE(30);
const sf::Color SUBTITLE_COLOR(sf::Color::Black);
const sf::Text::Style SUBTITLE_STYLE(sf::Text::Style::Underlined);
const sf::Vector2f SUBTITLE_POSITION({75.f, 110.f});

const unsigned int TEXT_SIZE(20);
const sf::Color TEXT_COLOR(sf::Color::Black);

const unsigned int GRID_BUTTON_CHAR_SIZE(52);
const sf::Color GRID_BUTTON_BG_COLOR(sf::Color::Transparent);
const sf::Color GRID_BUTTON_TEXT_COLOR(sf::Color::Black);

const unsigned int BACK_BUTTON_CHAR_SIZE(48);
const sf::Color BACK_BUTTON_BG_COLOR(sf::Color::Transparent);
const sf::Color BACK_BUTTON_TEXT_COLOR(sf::Color::Black);
const float BACK_BUTTON_POS_Y(425.f);

const sf::Color M_COLOR_BLUE(sf::Color(30, 30, 201, 255));
const sf::Color M_COLOR_BLUE_TRANSPARENT(sf::Color(30, 30, 201, 128));

#endif //OXO_GLOBALCONSTANTS_HPP
