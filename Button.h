#pragma once
#include<SFML/Graphics.hpp>

class Button
{
private:
	enum ButtonStates { IDLE = 0, HOVERD, PRESSED, ACTIVE };

	int ButtonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

public:
	Button(const float x, const float y, const float width, const float height, sf::Font* font, const std::string text,
	      sf::Color textdle_color, sf::Color text_hover_color, sf::Color text_active_color,
		  sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		  sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent,
		  sf::Color outline_active_color = sf::Color::Transparent);

	virtual ~Button();

	const bool isActive() const;
	const bool isPressed() const;
	const bool isHovered() const;
	const std::string getText() const;
	const sf::Vector2f getPos() const;
	const sf::Vector2f getSize() const;
	const sf::FloatRect getBounds() const;

	void setText(const std::string text);
	void setPos(const float pos_x, const float pos_y);

	void update(const sf::Vector2i& MousePos);
	void render(sf::RenderTarget* window);
};
