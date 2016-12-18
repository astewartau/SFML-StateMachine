#include "State.hpp"

State::State() :
	_nextState(this) {
}

State* State::Execute(int deltaTime) {
	if (_window != nullptr && _stateMachine != nullptr) {
		Update(deltaTime);
		DrawAll();
	}
	return _nextState;
}

bool State::Init(StateMachine* stateMachine) {
	if (_stateMachine == nullptr) {
		if (stateMachine != nullptr) {
			_stateMachine = stateMachine;
			_window = stateMachine->GetWindow();

			InitState();
			return true;
		} else {
			// Given state machine is empty!
		}
	} else {
		// State already initialised!
	}

	return false;
}

void State::DrawAll() {
	_window->clear(sf::Color::Black);
	Draw();
	_window->display();
}