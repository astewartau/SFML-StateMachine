#include "StateMachine.hpp"

namespace sm {
	StateMachine::StateMachine(const std::shared_ptr<sf::RenderWindow>& window) :
		_window(window),
		_userQuit(false) {}

	StateMachine::StateMachine(const std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<State> initialState) :
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

	void StateMachine::AddState(std::shared_ptr<State> state) {
		_states.push_back(state);
	}

	void StateMachine::QueueStateChange(std::shared_ptr<State> state, Status status) {
		_actionQueue.push(std::make_pair(state, status));
	}

	std::shared_ptr<sf::RenderWindow> StateMachine::GetWindow() {
		return _window;
	}

	bool StateMachine::GetUserQuit() {
		return _userQuit;
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
		for (std::shared_ptr<State> state : _states) {
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
		for (std::shared_ptr<State> state : _states) {
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
			std::pair<std::shared_ptr<State>, Status> action = _actionQueue.front();
			_actionQueue.pop();

			// Check whether the state associated with the action is stored
			auto it = std::find(_states.begin(), _states.end(), action.first);

			// If the state is not stored, store it
			// otherwise, update the status of the state
			if (it == _states.end()) {
				AddState(action.first);
			} else {
				(*it)->SetStatus(action.second);
			}
		}
	}
}