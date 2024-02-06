#include "MTextbox.hpp"
#include <ctime>

/** * * * * * * **
 *  CONSTRUCTOR  *
 ** * * * * * * **/
MTextbox::MTextbox() : m_isSelected(false),  m_hasLimit(false), m_limit(0), m_cursor('|') {
    m_textbox.setString("");
}

MTextbox::MTextbox(const sf::Font &font, unsigned int characterSize, bool selected) : m_isSelected(selected),  m_hasLimit(false), m_limit(0), m_cursor('|') {
    m_textbox.setFont(font);
    m_textbox.setCharacterSize(characterSize);
    m_shape.setSize({m_textbox.getLocalBounds().width, m_textbox.getLocalBounds().height});
}

/** * * * * * * **
 *  TEXT SETTER  *
 ** * * * * * * **/
void MTextbox::setFont(const sf::Font &font) {
    m_textbox.setFont(font);
}

void MTextbox::setCharacterSize(unsigned int characterSize) {
    m_textbox.setCharacterSize(characterSize);
    setTextboxSize(getTextboxSize());
}

void MTextbox::setTextStyle(sf::Uint32 style) {
    m_textbox.setStyle(style);
}

void MTextbox::setTextFillColor(const sf::Color &color) {
    m_textbox.setFillColor(color);
}

void MTextbox::setTextOutlineColor(const sf::Color &color) {
    m_textbox.setOutlineColor(color);
}

void MTextbox::setTextOutlineThickness(float thickness) {
    m_textbox.setOutlineThickness(thickness);
}

/** * * * * * * **
 *  TEXT GETTER  *
 ** * * * * * * **/
std::string MTextbox::getText() const {
    return m_textbox.getString();
}

std::wstring MTextbox::getTextWstring() const {
    return m_textbox.getString();
}

/** * * * * * * **
 *  SHAPE SETTER *
 ** * * * * * * **/
void MTextbox::setTextboxSize(const sf::Vector2f &buttonSize) {
    // Check that the shape size is not smaller than the text size
    if((buttonSize.x < m_textbox.getLocalBounds().width) && (buttonSize.y < m_textbox.getLocalBounds().height)){
        m_shape.setSize({m_textbox.getLocalBounds().width, m_textbox.getLocalBounds().height});
    }
    if((buttonSize.x < m_textbox.getLocalBounds().width) && (buttonSize.y >= m_textbox.getLocalBounds().height)){
        m_shape.setSize({m_textbox.getLocalBounds().width, buttonSize.y});
    }
    if((buttonSize.x >= m_textbox.getLocalBounds().width) && (buttonSize.y < m_textbox.getLocalBounds().height)){
        m_shape.setSize({buttonSize.x, m_textbox.getLocalBounds().height});
    }
    if((buttonSize.x >= m_textbox.getLocalBounds().width) && (buttonSize.y >= m_textbox.getLocalBounds().height)){
        m_shape.setSize(buttonSize);
    }
}

void MTextbox::setTextboxTexture(const sf::Texture *texture, bool resetRect) {
    m_shape.setTexture(texture, resetRect);
}

void MTextbox::setTextboxTextureRect(const sf::IntRect &rect) {
    m_shape.setTextureRect(rect);
}

void MTextbox::setTextboxFillColor(const sf::Color &color) {
    m_shape.setFillColor(color);
}

void MTextbox::setTextboxOutlineColor(const sf::Color &color) {
    m_shape.setOutlineColor(color);
}

void MTextbox::setTextboxOutlineThickness(float thickness) {
    m_shape.setOutlineThickness(thickness);
}

/** * * * * * * **
 *  SHAPE GETTER *
 ** * * * * * * **/
sf::Vector2f MTextbox::getTextboxSize() const {
    return m_shape.getSize();
}

/** * * * * * * **
 *    SETTER     *
 ** * * * * * * **/
void MTextbox::setLimit(bool ToF) {
    m_hasLimit = ToF;
}

void MTextbox::setLimit(bool ToF, int newLimit) {
    m_hasLimit = ToF;
    m_limit = newLimit;
}

void MTextbox::setSelected(bool ToF) {
    m_isSelected = ToF;

    if(!m_isSelected){
        std::string oldT(m_textbox.getString());
        if(oldT[oldT.length()-1] == m_cursor){
            //Variables
            std::string newT("");

            //Copy the whole string except the last character
            for (int i = 0; i < oldT.length()-1; ++i) {
                newT += oldT[i];
            }

            //Save the string
            m_textbox.setString(newT);
        }
    }
}

/** * * * * * * **
 *    GETTER     *
 ** * * * * * * **/
bool MTextbox::isSelected() const {
    return m_isSelected;
}

/** * * * * * * **
 *   FUNCTIONS   *
 ** * * * * * * **/
// Used to create the button if the first constructor has been used
void MTextbox::create(const sf::Font &font, unsigned int characterSize, bool selected) {
    m_isSelected = selected;
    m_hasLimit = false;
    m_limit = 0;
    m_textbox.setFont(font);
    m_textbox.setCharacterSize(characterSize);
    m_shape.setSize({m_textbox.getLocalBounds().width, m_textbox.getLocalBounds().height});
}

void MTextbox::setPosition(sf::Vector2f position) {
    m_shape.setPosition(position);
    m_textbox.setPosition(position.x + (m_shape.getLocalBounds().height / 4),
                          position.y + ((float)m_textbox.getCharacterSize() / 4));
}

sf::Vector2f MTextbox::getPosition() const {
    return m_textbox.getPosition();
}

// Check if the mouse is over the button
bool MTextbox::isMouseOver(sf::RenderWindow &window) const {
    float mouseX = (float)sf::Mouse::getPosition(window).x;
    float mouseY = (float)sf::Mouse::getPosition(window).y;

    float txbLowerLimitX = m_shape.getPosition().x;
    float txbUpperLimitX = txbLowerLimitX + m_shape.getSize().x;
    float txbLowerLimitY = m_shape.getPosition().y;
    float txbUpperLimitY = txbLowerLimitY + m_shape.getSize().y;

    if(mouseX > txbLowerLimitX && mouseX < txbUpperLimitX && mouseY > txbLowerLimitY && mouseY < txbUpperLimitY){
        return true;
    }else{
        return false;
    }
}

void MTextbox::typedOn(sf::Event input) {
    if(m_isSelected){
        unsigned int charTyped = input.text.unicode;
        if(charTyped < 128){
            if(m_hasLimit){
                if(m_text.str().length() < m_limit){
                    inputLogic(charTyped);
                }else if(m_text.str().length() >= m_limit && charTyped == DELETE_KEY){
                    deleteLastChar();
                }
            }else{
                inputLogic(charTyped);
            }
        }
    }
}

void MTextbox::updateCursor() {
    if(m_isSelected){
        std::time_t timestamp = std::time(nullptr);
        if(timestamp % 2){
            //Displays the string with the "_"
            std::string temp(m_textbox.getString());
            if(temp[temp.length()-1] != m_cursor){
                m_textbox.setString(m_textbox.getString() + m_cursor);
            }
        }else{
            //Displays the string without the "_"
            //Variables
            std::string oldT(m_text.str());
            std::string newT("");

            //Copy the whole string except the last character
            for (int i = 0; i < oldT.length(); ++i) {
                newT += oldT[i];
            }

            //Save the string
            m_textbox.setString(newT);
        }
    }
}

/** * * * * * * * **
 * INTERNAL LOGIC  *
 ** * * * * * * * **/
void MTextbox::deleteLastChar() {
    //Variables
    std::string oldT(m_text.str());
    std::string newT("");

    //Copy the whole string except the last character
    for (int i = 0; i < oldT.length()-1; ++i) {
        newT += oldT[i];
    }

    //Reset the stream
    m_text.str("");
    m_text << newT;

    //Save the string
    m_textbox.setString(m_text.str());
}

void MTextbox::inputLogic(unsigned int charTyped) {
    if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY){
        m_text << static_cast<char>(charTyped);
    }else if(charTyped == DELETE_KEY){
        if(!m_text.str().empty()){
            deleteLastChar();
        }
    }
    //Displays the string with a "_" to indicate that the user is writing into it
    m_textbox.setString(m_text.str() + m_cursor);
}

/** * * * * * * * * * * **
 * DRAWABLE SFML ELEMENT *
 ** * * * * * * * * * * **/
void MTextbox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_shape);
    target.draw(m_textbox);
}

