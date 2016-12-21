# SFML-StateMachine
**SFML-StateMachine** is a *state machine*, *state manager* or *screen manager* for the [SFML library](http://www.sfml-dev.org/), written in C++.

# Installation
Install SFML-StateMachine by adding the StateMachine folder or the files therein to your project, including:
- [State.hpp](StateMachine/State.hpp)
- [StateMachine.hpp](StateMachine/StateMachine.hpp)
- [StateMachine.cpp](StateMachine/StateMachine.cpp)

## Dependencies
This project requires SFML. SFML version 2.4.1 has been tested, but this project should work with any 2.x version.

# Usage


To run the state machine, use ```StateMachine.Execute()```. This will perform one 'execution' of the StateMachine. This may cause State changes and draw calls to be made. The result is a new frame output to the SFML window.

States can be *active*, *paused* or *inactive*. To set a state's status, use ```State.QueueStateChange(std::shared_ptr<State> state, Status status)```.

## Demo file
```cpp
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
		_rectangle.move(0.2f * deltaTime.asMilliseconds(),
			0.2f * deltaTime.asMilliseconds());

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
	std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>();
	window->create(sf::VideoMode(640, 480), "Window");

	sm::StateMachine stateMachine(window);
	stateMachine.AddState(std::make_shared<DemoState>());

	while (!stateMachine.UserQuit()) {
		stateMachine.Execute();
		sf::sleep(sf::milliseconds(5));
	}

	window->close();

	printf("Press ENTER to exit");
	std::getchar();
	return 0;
}
```

# Documentation
For detailed documentation, please see the comments within the two header files:
- [StateMachine.hpp](StateMachine/StateMachine.hpp)
- [State.hpp](StateMachine/State.hpp)

# Development
For current development status, please see the [issues page](https://github.com/astewartau/SFML-StateMachine/issues).

# Contributions
Contributions are welcome! Feel free to address issues, or add issues you have identified to the [issues page](https://github.com/astewartau/SFML-StateMachine/issues). Comments, feedback and advice are greatly appreciated.