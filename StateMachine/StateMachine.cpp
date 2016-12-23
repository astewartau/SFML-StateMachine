#include "StateMachine.hpp"
#include <algorithm>

namespace sm {
	StateMachine::StateMachine(std::shared_ptr<State> initialState) {
		AddState(initialState);
	}

	void StateMachine::AddState(std::shared_ptr<State> state) {
		if (std::find(_states.begin(), _states.end(), state) == _states.end()) {
			_states.push_back(state);
		}
	}

	void StateMachine::QueueStatusChange(const State* state, Status status) {
		if (_actionQueue.find(state) == _actionQueue.end()) {
			_actionQueue.insert(std::make_pair(state, status));
		}
	}

	void StateMachine::QueueRemoveState(const State* state) {
		if (_removeQueue.find(state) == _removeQueue.end()) {
			_removeQueue.insert(state);
		}
	}

	void StateMachine::UpdateStates() {
		int numStates = _states.size();
		for (int i = 0; i < numStates; i++) {
			switch (_states[i]->GetStatus()) {
			case Status::ACTIVATED:
				_states[i]->Update(_clock.restart());
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

	void StateMachine::ClearAll() {
		_states.clear();
		_actionQueue.clear();
		_removeQueue.clear();
	}

	void StateMachine::ProcessStateChanges() {
		for (std::pair<const State*, Status> action : _actionQueue) {
			for (auto it = _states.begin(); it != _states.end(); it++) {
				if (it->get() == action.first) {
					(*it)->SetStatus(action.second);
				}
			}
		}
		_actionQueue.clear();

		while (!_removeQueue.empty()) {
			const State* state = *_removeQueue.begin();
			_removeQueue.erase(_removeQueue.begin());

			for (auto it = _states.begin(); it != _states.end(); it++) {
				if (it->get() == state) {
					_states.erase(it);
					break;
				}
			}
		}
	}
}