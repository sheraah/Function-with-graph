#include "Button.h"


Button::Button(const float pos_x, const  float pos_y, const  float width, const float height, sf::Font* font, std::string text,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Color outline_idle_color,
	sf::Color outline_hover_color, sf::Color outline_active_color)

	:font(font), textIdleColor(text_idle_color), textHoverColor(text_hover_color), textActiveColor(text_active_color),
	idleColor(idle_color), hoverColor(hover_color), activeColor(active_color), outlineIdleColor(outline_idle_color),
	outlineHoverColor(outline_hover_color), outlineActiveColor(outline_active_color){
	ButtonState = IDLE;

	shape.setPosition(pos_x, pos_y);
	shape.setFillColor(idleColor);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(outlineIdleColor);
	shape.setSize({ width, height });

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize((width / 6.5 / text.length() * 10) * 0.90);
	this->text.setPosition(
		shape.getPosition().x + (width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		shape.getPosition().y + (height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

}

Button::~Button(){
}

const bool Button::isActive() const{
	return ButtonState == ACTIVE;
}

const bool Button::isPressed() const{
	return ButtonState == PRESSED;
}

const std::string Button::getText() const{
	return text.getString();
}

const bool Button::isHovered() const{
	return ButtonState == HOVERD || isActive() || isPressed();
}

void Button::setText(const std::string text){
	this->text.setString(text);

	setPos(getPos().x, getPos().y);
}

const sf::Vector2f Button::getPos() const{
	return shape.getPosition();
}

const sf::Vector2f Button::getSize() const{
	return shape.getSize();
}

void Button::setPos(const float pos_x, const float pos_y){
	shape.setPosition(pos_x, pos_y);

	text.setPosition(
		pos_x + (getBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
		pos_y + (getBounds().height / 2.f) - text.getGlobalBounds().height / 2.f
	);
}

const sf::FloatRect Button::getBounds() const{
	return shape.getGlobalBounds();
}

void Button::update(const sf::Vector2i& MousePos){
	static bool Pressed = false;
	ButtonState = IDLE;

	if (shape.getGlobalBounds().contains(sf::Vector2f(MousePos))){
		ButtonState = HOVERD;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			if (!Pressed) {
				Pressed = true;
				ButtonState = PRESSED;
				return;
			}
			ButtonState = ACTIVE;
		}
		else {
			Pressed = false;
		}
	}

	switch (ButtonState)
	{
	case IDLE:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;

	case HOVERD:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;

	case ACTIVE:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		shape.setOutlineColor(outlineActiveColor);
		break;
	}
}

void Button::render(sf::RenderTarget* window){
	window->draw(shape);
	window->draw(text);
}
