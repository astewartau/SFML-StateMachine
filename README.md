# SFML-StateMachine
**SFML-StateMachine** is a *state machine*, *state manager* or *screen manager* for the SFML library in C++ (http://www.sfml-dev.org/). It can be used to manage and run game **screens** or **states**.

# Installation
You can set up SFML-StateMachine by adding the StateMachine folder or the files therein to your project. This includes:
- ```State.cpp```
- ```State.hpp```
- ```StateMachine.cpp```
- ```StateMachine.hpp```

# Usage
## Writing custom states
An initial state called ```DemoState.hpp``` has been provided to demonstrate the basic usage. Custom states are built by extending the virtual class State, making sure to override the virtual methods ```InitState()```, ```Update(int deltaTime)``` and ```Draw()```. The DemoState is also provided below:
```cpp
#pragma once
#include "State.hpp"

class DemoState : public State {
private:
	void InitState() {
		// State initialisation
		_rectangle.setSize(sf::Vector2f(200, 150));
		_rectangle.setFillColor(sf::Color::Red);
		_rectangle.setPosition(20, 20);
	}

	void Update(int deltaTime) {
		// State logic
	}

	void Draw() {
		// Draw calls
		_window->draw(_rectangle);
	}

	sf::RectangleShape _rectangle;
};
```

## Running states using the StateMachine
The DemoState above has been used in an example application in ```main.cpp```, additionally provided below:

```cpp
#include "StateMachine/StateMachine.hpp"
#include "DemoState.hpp"

int main() {
	StateMachine stateMachine;
	stateMachine.SetState(new DemoState());
	stateMachine.Run();

	printf("Press ENTER to exit");
	std::getchar();
	return 0;
}
```

To run a StateMachine, a StateMachine object must be created, and an initial state must be set. The ```Run()``` function initiates the **game loop**.

# Documentation
For detailed documentation, please see the comments within the two header files:
- ```StateMachine.hpp```
- ```State.hpp```

# Contributions
This is one of my first open-source projects. As I am relatively new to C++, feedback, advice and contributions are greatly appreciated! For those of you who are new to SFML or managing states, I hope my solution proves useful or insightful!
