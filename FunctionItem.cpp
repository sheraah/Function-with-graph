#include "FunctionItem.h"

FunctionItem::FunctionItem(Game* game, void(Game::* drawText)(const std::string&, const sf::Vector2f, const sf::Color, const unsigned int),
	void(Game::* addLine)(sf::VertexArray*, const sf::Vector2f, const sf::Vector2f, const int, const sf::Color),
	sf::Vector2f(Game::* CoordsToPos)(const sf::Vector2f), const std::string TextBeforeFunc, const sf::Vector2f Pos, const float MultValue, sf::Font* font):
	game(game), drawText(drawText), addLine(addLine), CoordsToPos(CoordsToPos), TextBeforeFunc(TextBeforeFunc), Pos(Pos),
	color(generateRandomColor()), MultValue(MultValue), ChSize(MultValue * 20), needDelete(false) {

	textbox.reset(new Textbox(Pos.x + ChSize * TextBeforeFunc.length(), Pos.y, ChSize, 25, false, font));
	textbox->setColor(color);

	Graph.setPrimitiveType(sf::Lines);
}

sf::Color FunctionItem::generateRandomColor() {
	return sf::Color::Color(rand() % 256, rand() % 256, rand() % 256, 255);
}

void FunctionItem::resetColor() {
	color = generateRandomColor();
	textbox->setColor(color);
}

void FunctionItem::updateText(sf::Event evnt) {
	if (evnt.type == sf::Event::TextEntered) {
		if (evnt.key.code == 27) {
			textbox->setSelected(false);
			return;
		}

		textbox->input(evnt.key.code);
	}
}

void FunctionItem::resetGraph(const int& MaxGraphV) {
	Graph.clear();

	auto replace = [this](const std::string Value) {
		std::string eq = textbox->getString();

		for (int i = 0; i < eq.length(); i++) {
			if (eq[i] == 'X' || eq[i] == 'x') {
				eq.erase(eq.begin() + i);
				size_t index = i;
				if(i - 1 > 0)
					if (eq[i - 1] >= '0' && eq[i - 1] <= '9') {
						eq.insert(eq.begin() + i, '*');
						index++;
					}
				for (int k = 0; k < Value.length(); k++) {
					eq.insert(eq.begin() + index, Value[Value.size() - k - 1]);
				}
			}
		}
		return eq;
	};


	for (float i = -MaxGraphV; i <= MaxGraphV; i+= 1.f) {

		if (i + 1.f <= MaxGraphV) {
			int error = 0;
			std::string expression = replace(std::to_string(i));
			float result1 = static_cast<float>(te_interp(expression.c_str(), &error));
			expression = replace(std::to_string(i + 1.f));
			float result2 = static_cast<float>(te_interp(expression.c_str(), &error));

			if (error != 0) {
				return;
			}

			(game->*addLine)(&Graph, (game->*CoordsToPos)({ i, result1 }), (game->*CoordsToPos)({ i + 1, result2 }), MultValue * 2.f, color);
		}
	}
}

void FunctionItem::update(sf::Vector2i& MousePos, const sf::Keyboard::Key& Key, const int& MaxGraphV){
	textbox->update(static_cast<sf::Vector2f>(MousePos));

	if (textbox->getSelected()) {
		if (sf::Keyboard::isKeyPressed(Key)) {
			resetColor();
			return;
		}
	}

	resetGraph(MaxGraphV);
}

void FunctionItem::render(sf::RenderWindow* window){
	(game->*drawText)(TextBeforeFunc, Pos, color, ChSize);

	textbox->render(window);

	window->draw(Graph);
}
