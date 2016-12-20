#pragma once
#include "StateMachine/State.hpp"
#include "StateMachine/StateMachine.hpp"

class DemoState : public sm::State {
public:
	DemoState() {
		_rectangle.setSize(sf::Vector2f(200, 150));
		_rectangle.setFillColor(sf::Color::Red);
		_rectangle.setPosition(20, 20);
	}

private:
	void Update(sf::Time deltaTime) {
		// The rectangle moves with time
		_rectangle.move(0.2 * deltaTime.asMilliseconds(), 
			0.2 * deltaTime.asMilliseconds());

		// Pause the state when the rectangle nears the bottom 
		// of the screen
		if (_rectangle.getGlobalBounds().left > 300) {
			SetStatus(sm::Status::PAUSED);
		}
	}

	void Draw(sf::RenderWindow* window) {
		window->draw(_rectangle);
	}

	sf::RectangleShape _rectangle;
};

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(640, 480), "Window");

	sm::StateMachine* stateMachine = new sm::StateMachine(&window);
	stateMachine->AddState(new DemoState());

	while (!stateMachine->UserQuit()) {
		stateMachine->Execute();
		sf::sleep(sf::milliseconds(5));
	}
	
	delete stateMachine;
	window.close();

	printf("Press ENTER to exit");
	std::getchar();
	return 0;
}
