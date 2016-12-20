#include "StateMachine.hpp"

namespace sm {
	StateMachine::StateMachine(sf::RenderWindow* window) : 
		_window(window),
		_userQuit(false) {}

	StateMachine::StateMachine(sf::RenderWindow * window, State * initialState) :
		_window(window),
		_userQuit(false) {
		AddState(initialState);
	}

	void StateMachine::Execute() {
		ProcessInput();
		UpdateStates();
		DrawStates();
		ProcessStateChanges();
	}

	void StateMachine::AddState(State* state) {
		_states.push_back(state);
	}

	void StateMachine::QueueStateChange(State* state, Status status) {
		_actionQueue.push(std::make_pair(state, status));
	}

	sf::RenderWindow* StateMachine::GetWindow() {
		return _window;
	}

	bool StateMachine::UserQuit() {
		return _userQuit;
	}

	StateMachine::~StateMachine() {
		for (auto it = _states.begin(); it != _states.end(); ++it) {
			delete *it;
		}
		_states.clear();
	}

	void StateMachine::ProcessInput() {
		sf::Event event;
		while (_window->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				_userQuit = true;
				break;
			}
		}
	}

	void StateMachine::UpdateStates() {
		for (State* state : _states) {
			switch (state->GetStatus()) {
			case Status::ACTIVATED:
				state->Update(_clock.restart());
				break;
			case Status::PAUSED:
				break;
			case Status::DEACTIVATED:
				break;
			}
		}
	}

	void StateMachine::DrawStates() {
		_window->clear();
		for (State* state : _states) {
			switch (state->GetStatus()) {
			case Status::ACTIVATED:
				state->Draw(_window);
				break;
			case Status::PAUSED:
				state->Draw(_window);
				break;
			case Status::DEACTIVATED:
				break;
			}
		}
		_window->display();
	}

	void StateMachine::ProcessStateChanges() {
		while (!_actionQueue.empty()) {
			// Get the next action
			std::pair<State*, Status> action = _actionQueue.front();
			_actionQueue.pop();

			// Check whether the state associated with the action is stored
			auto it = std::find(_states.begin(), _states.end(), action.first);

			// If the state is not stored, store it
			// otherwise, update the status of the state
			if (it == _states.end()) {
				AddState(*it);
			} else {
				(*it)->SetStatus(action.second);
			}
		}
	}
}