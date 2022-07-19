#include "Game.h"

Game::Game(const sf::VideoMode Res, const sf::String AppName, const int MaxGraphValue): MaxGraphV(MaxGraphValue), MaxFunctionItems(9), 
deleteKey(sf::Keyboard::Delete), canDelete(true) {
	initWindow(Res, AppName);
	initVariables();
	initGraph();
}

sf::Vector2f Game::CoordsToPos(const sf::Vector2f Coords)
{ 
	sf::Vector2f SpaceBetweenLines = { WindowSize.x / MaxGraphV / 2.f,
		WindowSize.y / MaxGraphV / 2.f};

	return sf::Vector2f((WindowSize.x / 2.f) + (Coords.x * SpaceBetweenLines.x),
		(WindowSize.y / 2.f) - (Coords.y * SpaceBetweenLines.y));
}

void Game::initWindow(const sf::VideoMode& Res, const sf::String& AppName){
	window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(Res, AppName, sf::Style::Close));
}

void Game::initVariables(){
	font.loadFromFile("Fonts/Stan.ttf");
	text.setFont(font);

	MultValue = (window->getSize().x / window->getSize().y) * (15.f / static_cast<float>(MaxGraphV));
	WindowSize = static_cast<sf::Vector2f>(window->getSize());
	updateTimer.reset(new Timer(0.1f));

	ColorKeys.reset(new Combo<sf::Keyboard::Key>("Change color key", &font, sf::Color::Cyan, Button(WindowSize.x - WindowSize.x / 7.f, 100.f,
		WindowSize.x / 7.f, WindowSize.x / 30.f, &font, "Shift Left", sf::Color::Color(42, 169, 189),
		sf::Color::Color(30, 105, 117), sf::Color::Color(30, 105, 117), sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent),
		{
			{ "Shift Left", sf::Keyboard::LShift},
			{ "Shift Right", sf::Keyboard::RShift},
			{ "Enter", sf::Keyboard::Enter},
			{ "Arrow Left", sf::Keyboard::Left},
			{ "Arrow Right", sf::Keyboard::Right},
			{ "Arrow Down", sf::Keyboard::Down},
			{ "Arrow Up", sf::Keyboard::Up}
		}));
	sf::Vector2f addButtonPos = { WindowSize.x / 15, 0.f };
	sf::Vector2f addButtonSize = { addButtonPos.x , addButtonPos.x / 2.f };
	addButton.reset(new Button(addButtonPos.x, addButtonPos.y, addButtonSize.x, addButtonSize.y, &font, "Add", sf::Color::Color(42, 169, 189),
		sf::Color::Color(30, 105, 117), sf::Color::Color(30, 105, 117), sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent));


}

void Game::addLine(sf::VertexArray* vert, const sf::Vector2f Pos1, const sf::Vector2f Pos2, const int Thickness, const sf::Color color) {
	sf::Vertex point;
	point.color = color;

	for (float i = 0; i <= Thickness; i += 0.5f) {
		float L = sqrt((Pos1.x + Pos2.x) * (Pos1.x + Pos2.x) + (Pos1.y + Pos2.y) * (Pos1.y + Pos2.y));
		sf::Vector2f NewPos = { Pos1.x + (i - Thickness / 2) * (Pos2.y - Pos1.y) / L, Pos1.y + (i - Thickness / 2) * (Pos1.x - Pos2.x) / L };
		point.position = { NewPos.x , NewPos.y };
		vert->append(point);

		NewPos = { Pos2.x + (i - Thickness / 2) * (Pos2.y - Pos1.y) / L, Pos2.y + (i - Thickness / 2) * (Pos1.x - Pos2.x) / L };
		point.position = { NewPos.x, NewPos.y };
		vert->append(point);
	}
}

void Game::initGraph(){
	GraphLines.setPrimitiveType(sf::Lines);

	for (float i = MaxGraphV - 1; i > -MaxGraphV; i -= 1.f) {
		int Thickness = i == 0 ? MultValue * 3 : MultValue * 0.5;
	
		addLine(&GraphLines, CoordsToPos({ -static_cast<float>(MaxGraphV), i }), CoordsToPos({ static_cast<float>(MaxGraphV), i }), Thickness, sf::Color::Black);
	
		addLine(&GraphLines, CoordsToPos({ i, static_cast<float>(MaxGraphV) }), CoordsToPos({ i, -static_cast<float>(MaxGraphV) }), Thickness, sf::Color::Black);
	}
}

void Game::pollEvents(){
	sf::Event evnt;
	while (window->pollEvent(evnt)) {
		switch (evnt.type) {
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::KeyReleased:
			if (evnt.key.code == deleteKey) {
				canDelete = true;
			}
			break;
		}
		for (const auto& f : functionItems) f->updateText(evnt);
	}
}

void Game::update(const float& dt){
	MousePos = sf::Mouse::getPosition(*window);
	addButton->update(MousePos);

	if (addButton->isPressed() && functionItems.size() < MaxFunctionItems) {
		functionItems.push_back(std::unique_ptr<FunctionItem>(new FunctionItem(this, &Game::drawText, &Game::addLine, &Game::CoordsToPos,
			std::to_string(functionItems.size() + 1), { addButton->getPos().x, (functionItems.size() + 1) * WindowSize.y / 20.f}, WindowSize.x / WindowSize.y, &font)));
	}

	if (functionItems.size() > 0) {
		if (sf::Keyboard::isKeyPressed(deleteKey)) {
			if (!canDelete) return;
			canDelete = false;
			size_t index = functionItems.size() - 1;
			functionItems[index].reset(nullptr);
			functionItems.erase(functionItems.begin() + index);
		}
	}

	if (updateTimer->timerOver(dt)) {

		for (size_t i = 0; i < functionItems.size(); i++) {
			functionItems[i]->update(MousePos, ColorKeys->getActiveValue(), MaxGraphV);
			if (sf::Keyboard::isKeyPressed(deleteKey)) {
				size_t index = functionItems.size() - 1;
				functionItems[index].reset(nullptr);
				functionItems.erase(functionItems.begin() + index);
			}
		}
	}

	ColorKeys->update(MousePos);
}

void Game::render(){
	window->clear(sf::Color::White);

	draw();

	window->display();
}

void Game::drawText(const std::string& str, const sf::Vector2f Pos, const sf::Color color, const unsigned int ChSize) {
	text.setPosition(Pos);
	text.setFillColor(color);
	text.setCharacterSize(ChSize);
	text.setString(str);

	window->draw(text);

	ColorKeys->render(window.get());
}

void Game::draw(){
	window->draw(GraphLines);

	for (float i = -MaxGraphV + 1; i < MaxGraphV; i+= 1.f) {
		if (i == 0) continue;
		std::string str = std::to_string(static_cast<int>(i));
		const unsigned ChSize = MultValue * 20;

		sf::Vector2f Pos = CoordsToPos({ i, 0 });
		drawText(str, { Pos.x - ((ChSize * str.length()) / 1.5f ), Pos.y }, sf::Color::Black, ChSize);
		Pos = CoordsToPos({ 0, i });
		drawText(str, { Pos.x - ((ChSize * str.length()) / 1.5f ), Pos.y }, sf::Color::Black, ChSize);
	}

	for (const auto& f : functionItems) {
		f->render(window.get());
	}

	addButton->render(window.get());
}

void Game::run(){
	while (window->isOpen()) {
		const float dt = clock.restart().asSeconds();

		pollEvents();
		update(dt);
		render();
	}
}
