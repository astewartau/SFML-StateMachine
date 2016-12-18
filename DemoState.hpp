#pragma once
#include "StateMachine/State.hpp"

class DemoState : public State {
private:
	void InitState() {
		_rectangle.setSize(sf::Vector2f(200, 150));
		_rectangle.setFillColor(sf::Color::Red);
		_rectangle.setPosition(20, 20);
	}

	void Update(int deltaTime) {

	}

	void Draw() {
		_window->draw(_rectangle);
	}

	sf::RectangleShape _rectangle;
};
