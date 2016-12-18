#include "StateMachine.hpp"

StateMachine::StateMachine() {}

StateMachine::StateMachine(State* initialState) {
	SetState(initialState);
}

void StateMachine::SetState(State * newState) {
	if (_currentState != nullptr) {
		delete _currentState;
	}

	_currentState = newState;
	_currentState->Init(this);
}

void StateMachine::Run() {
	// Create SFML window
	_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	_clock.restart();

	// Game loop - continues as long as there is a valid state
	while (_currentState != nullptr) {
		PreLoop();
		ProcessInput();
		_currentState = _currentState->Execute(_clock.restart().asMilliseconds());
		PostLoop();
	}

	// Close the SFML window once the state is cleared
	_window.close();
}

void StateMachine::PreLoop() {}

void StateMachine::ProcessInput() {
	sf::Event event;
	while (_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			_currentState = nullptr;
			break;
		}
	}
}

void StateMachine::PostLoop() {
	//sf::sleep(sf::milliseconds(5));
}

sf::RenderWindow* StateMachine::GetWindow() {
	return &_window;
}
