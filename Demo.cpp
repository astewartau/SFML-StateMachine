#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine/State.hpp"
#include "StateMachine/StateMachine.hpp"

// Concrete extension of the virtual state class
class DemoState : public sm::State {
public:
	// Constructor initialises the state
	DemoState() {
		_rectangle.setSize(sf::Vector2f(200, 150));
		_rectangle.setFillColor(sf::Color::Red);
		_rectangle.setPosition(20, 20);
	}
private:
	// Update function contains state-specific logic
	void Update(sf::Time deltaTime) {
		// The rectangle moves with time
		_rectangle.move(0.2f * deltaTime.asMilliseconds(), 
			0.2f * deltaTime.asMilliseconds());

		// Pause the state when the rectangle nears the bottom 
		// of the screen
		if (_rectangle.getGlobalBounds().left > 300) {
			SetPaused(true);
		}
	}

	// Draw function contains SFML draw calls
	void Draw(const std::shared_ptr<sf::RenderWindow>& window) {
		window->draw(_rectangle);
	}

	sf::RectangleShape _rectangle;
};

int main() {
	// Create window
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>();
	window->create(sf::VideoMode(640, 480), "StateMachine demo");

	// Create state machine using demo state
	sm::StateMachine stateMachine(std::make_shared<DemoState>());

	// Game loop
	bool quit = false;
	while (!quit) {
		// Process input
		sf::Event event;
		while (window->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				quit = true;
				break;
			}
		}

		// Update states
		stateMachine.UpdateStates();

		// Draw states
		window->clear();
		stateMachine.DrawStates(window);
		window->display();

		// Wait
		sf::sleep(sf::milliseconds(5));

	}
	
	// Cleanup
	stateMachine.ClearAll();
	window->close();
	return 0;
}
