#pragma once
#include "Button.h"
#include<vector>
#include<map>
#include<iostream>

template<typename T>
class Combo
{
private:
    std::vector<std::unique_ptr<Button>> buttons;
    std::map<std::string, T> Elements;
    sf::Text NameText;
    std::string Name;
    sf::Font* font;

    bool Show;

    void Swap(size_t index);

    std::string getMapValueByIndex(size_t index){
        auto it = Elements.begin();
        std::advance(it, index);
        return it->first;
    }

public:
    Combo(const std::string Name, sf::Font* font, sf::Color TextColor, 
        const Button ComboButton, const std::map<std::string, T> ElementsAndValues);

    virtual ~Combo();

    void setActive(const std::string index);
    void setPos(const float& X, const float& Y);

    const T& getActiveValue();
    const std::string getActiveString() const;

    void update(const sf::Vector2i& MousePos);
    void render(sf::RenderTarget* window);
};


template<typename T>
Combo<T>::Combo(const std::string Name, sf::Font* font, sf::Color TextColor,
    const Button ComboButton, const std::map<std::string, T> ElementsAndValues)
    :Elements(ElementsAndValues), font(font){
    Show = false;

    NameText.setFont(*font);
    NameText.setString(Name);
    NameText.setFillColor(TextColor);
    NameText.setCharacterSize(static_cast<unsigned int>(ComboButton.getSize().x / 8));

    for (size_t i = 0; i < Elements.size(); i++) {
        buttons.emplace_back(std::unique_ptr<Button>(new Button(ComboButton)));

        buttons[i]->setText(getMapValueByIndex(i));
    }

    setPos(ComboButton.getPos().x, ComboButton.getPos().y);
}

template<typename T>
Combo<T>::~Combo()
{
}

template<typename T>
inline void Combo<T>::setActive(const std::string index){
    for (size_t i = 1; i < buttons.size(); i++){
        if (getMapValueByIndex(i) == index){
            Swap(i);
            return;
        }
    }
}

template<typename T>
void Combo<T>::setPos(const float& X, const float& Y) {
    NameText.setPosition(X + buttons[0]->getSize().x / 2.f - NameText.getGlobalBounds().width / 2,
        X - NameText.getGlobalBounds().height * 1.7f);

    for (size_t i = 0; i < Elements.size(); i++) {
        if (i > 0) buttons[i]->setPos(buttons[i - 1]->getPos().x, buttons[i - 1]->getPos().y + buttons[i - 1]->getSize().y);
        else buttons[i]->setPos(buttons[i]->getPos().x, buttons[i]->getPos().y);
    }
}

template<typename T>
const T& Combo<T>::getActiveValue()
{
    return Elements[getActiveString()];
}

template<typename T>
const std::string Combo<T>::getActiveString() const
{
    return buttons[0]->getText();
}

template<typename T>
void Combo<T>::Swap(size_t index)
{
    const std::string temp = buttons[0]->getText();
    buttons[0]->setText(buttons[index]->getText());
    buttons[index]->setText(temp);
}


template<typename T>
void Combo<T>::update(const sf::Vector2i& MousePos)
{
    static bool canMouseBePressed = true;
    bool hovered = false;

    buttons[0]->update(MousePos);

    if (buttons[0]->isHovered())
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && canMouseBePressed)
        {
            Show = !Show;
            canMouseBePressed = false;
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) canMouseBePressed = true;

        hovered = true;
    }

    if (Show)
    {
        for (size_t i = 1; i < buttons.size(); i++)
        {
            buttons[i]->update(MousePos);

            if (buttons[i]->isHovered())
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    Swap(i);
                    Show = false;
                    break;
                }
                hovered = true;
            }
        }

        if (!hovered)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                Show = false;
        }
    }
}

template<typename T>
void Combo<T>::render(sf::RenderTarget* window)
{
    window->draw(NameText);
    if (Show)
        for (const auto& B : buttons) B->render(window);
    else
        buttons[0]->render(window);
}