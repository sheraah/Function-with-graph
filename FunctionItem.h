#pragma once
#include "Textbox.h"
#include "Button.h"
#include "tinyexpr.h"

class Game;

class FunctionItem{
private:
	Game* game;
	const sf::Vector2f Pos;
	const std::string TextBeforeFunc;
	const float MultValue;
	sf::VertexArray Graph;
	std::unique_ptr<Textbox> textbox;
	const unsigned int ChSize;
	bool needDelete;
	sf::Color color;

	void(Game::*drawText)(const std::string&, const sf::Vector2f, const sf::Color, const unsigned int);
	void(Game::*addLine)(sf::VertexArray*, const sf::Vector2f, const sf::Vector2f, const int, const sf::Color);
	sf::Vector2f(Game::* CoordsToPos)(const sf::Vector2f);

	sf::Color generateRandomColor();
	void resetColor();
	void resetGraph(const int& MaxGraphV);


public:
	FunctionItem(Game* game, void(Game::* drawText)(const std::string&, const sf::Vector2f, const sf::Color, const unsigned int),
		void(Game::* addLine)(sf::VertexArray*, const sf::Vector2f, const sf::Vector2f, const int, const sf::Color),
		sf::Vector2f(Game::* CoordsToPos)(const sf::Vector2f), const std::string TextBeforeFunc, const sf::Vector2f Pos, const float MultValue, sf::Font* font);

	void updateText(sf::Event evnt);
	void update(sf::Vector2i& MousePos, const sf::Keyboard::Key& Key, const int& MaxGraphV);
	void render(sf::RenderWindow* window);
	const bool& getNeedDetete() const { return needDelete; };
};

