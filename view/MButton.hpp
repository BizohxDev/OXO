#ifndef ESSAISSFML_MBUTTON_HPP
#define ESSAISSFML_MBUTTON_HPP

#include "SFML/Graphics.hpp"

class MButton : public sf::Drawable {
protected:
    sf::RectangleShape m_shape;
    sf::Text m_text;

private:
    // Drawable SFML element
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    // Constructors
    MButton();
    MButton(const std::wstring &text, const sf::Font &font, unsigned int characterSize);

    // Text setter
    void setText(const std::wstring &text);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int characterSize);
    void setTextStyle(sf::Uint32 style);
    void setTextFillColor(const sf::Color &color);
    void setTextOutlineColor(const sf::Color &color);
    void setTextOutlineThickness(float thickness);
    // Text getter

    // Shape setter
    void setButtonSize(const sf::Vector2f &buttonSize);
    void setButtonTexture(const sf::Texture *texture, bool resetRect=false);
    void setButtonTextureRect(const sf::IntRect &rect);
    void setButtonFillColor(const sf::Color &color);
    void setButtonOutlineColor(const sf::Color &color);
    void setButtonOutlineThickness(float thickness);
    // Shape getter
    sf::Vector2f getButtonSize() const;

    // Functions
    void create(const std::wstring &text, const sf::Font &font, unsigned int characterSize);
    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition() const;
    bool isMouseOver(sf::RenderWindow &window) const;
};


#endif //ESSAISSFML_MBUTTON_HPP
