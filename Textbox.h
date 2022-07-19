#pragma once
#include <SFML/Graphics.hpp>
#include<sstream>
#include<iostream>
#define SFML_NO_DEPRECATED_WARNINGS


class Textbox
{
private:
    const int DELETEKEY = 8;
    const int ENTERKEY = 13;
    const int ESCAPEKEY = 27;

    sf::Text textBox;
    sf::Font font;
    std::stringstream text;
    bool isSelected;
    unsigned int limit;
    void deleteLastCharacter();

public:
    Textbox(float pos_x, float pos_y, int chSize, unsigned int limt, bool isSel, sf::Font* font);

    Textbox();


    void setFont(std::string fontName);
    void setCharactersize(int chSize);
    void setSelected(bool isSel);
    void input(int charTyped);
    void setPos(float pos_x, float pos_y);
    void setLimit(unsigned int limit);
    void setColor(sf::Color color);
    void setOulineColor(sf::Color color);
    void setOutlineThickness(float Thickness);
    void setPosition(float x, float y);
    void update(const sf::Vector2f& MousePos);

    void setString(std::string newS);

    inline const std::string getString() const { return text.str(); };
    inline const unsigned int& getLimit() const { return limit; };
    inline const bool& getSelected() const { return isSelected; };
    inline const sf::Font& getFont() const { return font; };
    inline const sf::FloatRect getBounds() const { return textBox.getGlobalBounds(); };
    inline const size_t& getTextLength() const { return text.str().length(); };
    inline const float& getOutlineThickness() const { return textBox.getOutlineThickness(); };
    inline const sf::Vector2f& getPos() const { return textBox.getPosition(); };
    inline const int getCharacterSize() const { return textBox.getCharacterSize(); };
    inline const sf::Color& getColor() const { return textBox.getFillColor(); };

    void render(sf::RenderTarget* window);
};