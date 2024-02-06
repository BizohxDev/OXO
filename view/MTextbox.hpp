#ifndef OXO_MTEXTBOX_HPP
#define OXO_MTEXTBOX_HPP

#include "SFML/Graphics.hpp"
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class MTextbox : public sf::Drawable {
protected:
    sf::RectangleShape m_shape;
    sf::Text m_textbox;
    std::ostringstream m_text;
    bool m_isSelected;
    bool m_hasLimit;
    int m_limit;
    char m_cursor;

private:
    // Drawable SFML element
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Internal logic
    void deleteLastChar();
    void inputLogic(unsigned int charTyped);

public:
    // Constructor
    MTextbox();
    MTextbox(const sf::Font &font, unsigned int characterSize, bool selected);

    // Text setter
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int characterSize);
    void setTextStyle(sf::Uint32 style);
    void setTextFillColor(const sf::Color &color);
    void setTextOutlineColor(const sf::Color &color);
    void setTextOutlineThickness(float thickness);
    // Text getter
    std::string getText() const;
    std::wstring getTextWstring() const;

    // Shape setter
    void setTextboxSize(const sf::Vector2f &buttonSize);
    void setTextboxTexture(const sf::Texture *texture, bool resetRect=false);
    void setTextboxTextureRect(const sf::IntRect &rect);
    void setTextboxFillColor(const sf::Color &color);
    void setTextboxOutlineColor(const sf::Color &color);
    void setTextboxOutlineThickness(float thickness);
    // Shape getter
    sf::Vector2f getTextboxSize() const;

    // Setter
    void setLimit(bool ToF);
    void setLimit(bool ToF, int newLimit);
    void setSelected(bool ToF);

    // Getter
    bool isSelected() const;

    // Functions
    void create(const sf::Font &font, unsigned int characterSize, bool selected);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    bool isMouseOver(sf::RenderWindow &window) const;
    void typedOn(sf::Event input);
    void updateCursor();
};

#endif //OXO_MTEXTBOX_HPP
