#include "MButton.hpp"

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
MButton::MButton() {};

MButton::MButton(const std::wstring &text, const sf::Font &font, unsigned int characterSize) {
    m_text.setFont(font);
    m_text.setCharacterSize(characterSize);
    m_text.setString(text);
    m_shape.setSize({m_text.getLocalBounds().width, m_text.getLocalBounds().height});
}

/** * * * * * * **
 *  TEXT SETTER  *
 ** * * * * * * **/
void MButton::setText(const std::wstring &text) {
    m_text.setString(text);
}

void MButton::setFont(const sf::Font &font) {
    m_text.setFont(font);
}

void MButton::setCharacterSize(unsigned int characterSize) {
    m_text.setCharacterSize(characterSize);
    setButtonSize(getButtonSize());
}

void MButton::setTextStyle(sf::Uint32 style) {
    m_text.setStyle(style);
}

void MButton::setTextFillColor(const sf::Color &color) {
    m_text.setFillColor(color);
}

void MButton::setTextOutlineColor(const sf::Color &color) {
    m_text.setOutlineColor(color);
}

void MButton::setTextOutlineThickness(float thickness) {
    m_text.setOutlineThickness(thickness);
}

/** * * * * * * **
 *  TEXT GETTER  *
 ** * * * * * * **/

/** * * * * * * **
 *  SHAPE SETTER *
 ** * * * * * * **/
void MButton::setButtonSize(const sf::Vector2f &buttonSize) {
    // Check that the shape size is not smaller than the text size
    if((buttonSize.x < m_text.getLocalBounds().width) && (buttonSize.y < m_text.getLocalBounds().height)){
        m_shape.setSize({m_text.getLocalBounds().width, m_text.getLocalBounds().height});
    }
    if((buttonSize.x < m_text.getLocalBounds().width) && (buttonSize.y >= m_text.getLocalBounds().height)){
        m_shape.setSize({m_text.getLocalBounds().width, buttonSize.y});
    }
    if((buttonSize.x >= m_text.getLocalBounds().width) && (buttonSize.y < m_text.getLocalBounds().height)){
        m_shape.setSize({buttonSize.x, m_text.getLocalBounds().height});
    }
    if((buttonSize.x >= m_text.getLocalBounds().width) && (buttonSize.y >= m_text.getLocalBounds().height)){
        m_shape.setSize(buttonSize);
    }
}

void MButton::setButtonTexture(const sf::Texture *texture, bool resetRect) {
    m_shape.setTexture(texture, resetRect);
}

void MButton::setButtonTextureRect(const sf::IntRect &rect) {
    m_shape.setTextureRect(rect);
}

void MButton::setButtonFillColor(const sf::Color &color) {
    m_shape.setFillColor(color);
}

void MButton::setButtonOutlineColor(const sf::Color &color) {
    m_shape.setOutlineColor(color);
}

void MButton::setButtonOutlineThickness(float thickness) {
    m_shape.setOutlineThickness(thickness);
}

/** * * * * * * **
 *  SHAPE GETTER *
 ** * * * * * * **/
sf::Vector2f MButton::getButtonSize() const {
    return m_shape.getSize();
}

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
 // Used to create the button if the first constructor has been used
void MButton::create(const std::wstring &text, const sf::Font &font, unsigned int characterSize) {
    m_text.setFont(font);
    m_text.setCharacterSize(characterSize);
    m_text.setString(text);
    m_shape.setSize({m_text.getLocalBounds().width, m_text.getLocalBounds().height});
}

void MButton::setPosition(sf::Vector2f position) {
    // Set shape position
    m_shape.setPosition(position);
    // Center the text in the shape
    m_text.setPosition((position.x + ((m_shape.getLocalBounds().width / 2) - (m_text.getLocalBounds().width / 2)))-m_text.getLocalBounds().left,
                       (position.y + ((m_shape.getLocalBounds().height / 2) - (m_text.getLocalBounds().height / 2)))-m_text.getLocalBounds().top);
}

sf::Vector2f MButton::getPosition() const {
    return m_shape.getPosition();
}

// Check if the mouse is over the button
bool MButton::isMouseOver(sf::RenderWindow &window) const {
    float mouseX = (float)sf::Mouse::getPosition(window).x;
    float mouseY = (float)sf::Mouse::getPosition(window).y;

    float btnLowerLimitX = m_shape.getPosition().x;
    float btnUpperLimitX = btnLowerLimitX + m_shape.getSize().x;
    float btnLowerLimitY = m_shape.getPosition().y;
    float btnUpperLimitY = btnLowerLimitY + m_shape.getSize().y;

    if(mouseX > btnLowerLimitX && mouseX < btnUpperLimitX && mouseY > btnLowerLimitY && mouseY < btnUpperLimitY){
        return true;
    }else{
        return false;
    }
}

/** * * * * * * * * * * **
 * DRAWABLE SFML ELEMENT *
 ** * * * * * * * * * * **/
void MButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_shape);
    target.draw(m_text);
}
