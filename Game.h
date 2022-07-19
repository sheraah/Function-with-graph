#pragma once
#include "FunctionItem.h"
#include "Timer.h"
#include "Combo.h"

class Game{
private:
	std::unique_ptr<sf::RenderWindow> window;
	const int MaxGraphV;
	const int MaxFunctionItems;
	const sf::Keyboard::Key deleteKey;
	sf::Clock clock;
	bool canDelete;

	sf::VertexArray GraphLines;
	sf::Text text;
	std::vector<std::unique_ptr<FunctionItem>> functionItems;
	sf::Font font;
	float MultValue;
	std::unique_ptr<Button> addButton;
	sf::Vector2i MousePos;
	sf::Vector2f WindowSize;
	std::unique_ptr<Timer> updateTimer;
	std::unique_ptr<Combo<sf::Keyboard::Key>> ColorKeys;

	sf::Vector2f CoordsToPos(const sf::Vector2f Coords);
	void drawText(const std::string& str, const sf::Vector2f Pos, const sf::Color color, const unsigned int ChSize);
	void addLine(sf::VertexArray* vert, const sf::Vector2f Pos1, const sf::Vector2f Pos2, const int Thickness, const sf::Color color);
	void initWindow(const sf::VideoMode& Res, const sf::String& AppName);
	void initGraph();
	void initVariables();
	


	void update(const float& dt);
	void render();
	void draw();

public:
	void pollEvents();
	Game(const sf::VideoMode Res, const sf::String AppName, const int MaxGraphValue);
	virtual ~Game() { };
	void run();


};

