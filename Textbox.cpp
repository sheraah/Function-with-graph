#include "Textbox.h"

Textbox::Textbox(float pos_x, float pos_y, int chsize, unsigned int limit, bool isSel, sf::Font* font)
{
	textBox.setPosition(pos_x, pos_y);
	textBox.setCharacterSize(chsize);
	isSelected = isSel;
	this->limit = limit;
	textBox.setFont(*font);

	if (isSelected)
		textBox.setString("_");
	else
		textBox.setString("");

	text << std::string(textBox.getString());
}



Textbox::Textbox()
{
	textBox.setPosition(0, 0);
	textBox.setCharacterSize(0);
	isSelected = false;
	limit = 0;

	textBox.setString(" ");
}

void Textbox::setFont(std::string File)
{
	font.loadFromFile(File);
	textBox.setFont(font);
}

void Textbox::setCharactersize(int chsize)
{
	textBox.setCharacterSize(chsize);
}

void Textbox::setSelected(bool isSel)
{
	isSelected = isSel;

	if (!isSelected)
	{
		textBox.setString(" ");
		textBox.setString(text.str());
	}
	else
	{
		textBox.setString(text.str() + '_');
	}
}

void Textbox::input(int charTyped)
{
	if (isSelected)
	{
		if (charTyped != DELETEKEY && charTyped != ESCAPEKEY && charTyped != ENTERKEY)
			if (text.str().length() < limit)
				text << static_cast<char>(charTyped);

		if (charTyped == DELETEKEY)
			if (text.str().length() > 0)
				deleteLastCharacter();

		textBox.setString(text.str() + '_');
	}
}

void Textbox::update(const sf::Vector2f& MousePos) {
	if (std::string(textBox.getString()).length() < 2) {
		if (sf::FloatRect(textBox.getPosition().x, textBox.getPosition().y, 
			textBox.getCharacterSize() * 10, textBox.getCharacterSize()).contains(MousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			setSelected(true);
			return;
		}
	}

	if (textBox.getGlobalBounds().contains(MousePos)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			setSelected(true);
			return;
		}
	}
	else {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			setSelected(false);
			return;
		}
	}
}

void Textbox::setPos(float pos_x, float pos_y)
{
	textBox.setPosition(pos_x, pos_y);
}

void Textbox::deleteLastCharacter()
{
	std::string newT = std::string();
	for (size_t i = 0; i < text.str().length() - 1; i++)
		newT.push_back(text.str()[i]);

	text = std::stringstream();
	text << newT;
	textBox.setString("");
	textBox.setString(text.str());
}

void Textbox::setLimit(unsigned int limit)
{
	this->limit = limit;
}

void Textbox::setColor(sf::Color color)
{
	textBox.setFillColor(color);
}

void Textbox::setOulineColor(sf::Color color)
{
	textBox.setOutlineColor(color);
}

void Textbox::setOutlineThickness(float Thickness)
{
	textBox.setOutlineThickness(Thickness);
}

void Textbox::setPosition(float x, float y)
{
	textBox.setPosition(x, y);
}

void Textbox::setString(std::string newS)
{
	text.str(newS);

	if (isSelected == true)
		textBox.setString(text.str() + '_');

	else
		textBox.setString(text.str());
}

void Textbox::render(sf::RenderTarget* window)
{
	window->draw(textBox);
}