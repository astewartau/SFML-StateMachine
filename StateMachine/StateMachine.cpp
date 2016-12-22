#include "StateMachine.hpp"

namespace sm {
	StateMachine::StateMachine(std::shared_ptr<State> initialState) {
		AddState(initialState);
	}

	void StateMachine::AddState(std::shared_ptr<State> state) {
		_states.push_back(state);
	}

	void StateMachine::QueueStateChange(std::shared_ptr<State> state, Status status) {
		_actionQueue.push(std::make_pair(state, status));
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

		ProcessStateChanges();
	}

	void StateMachine::DrawStates(const std::shared_ptr<sf::RenderWindow>& window) {
		for (std::shared_ptr<State> state : _states) {
			switch (state->GetStatus()) {
			case Status::ACTIVATED:
				state->Draw(window);
				break;
			case Status::PAUSED:
				state->Draw(window);
				break;
			case Status::DEACTIVATED:
				break;
			}
		}
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