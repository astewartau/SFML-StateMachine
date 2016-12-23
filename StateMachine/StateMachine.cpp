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

	void StateMachine::QueueRemoveState(const State* state) {
		if (_removeQueue.find(state) == _removeQueue.end()) {
			_removeQueue.insert(state);
		}
	}

	void StateMachine::UpdateStates() {
		for (std::shared_ptr<State> state : _states) {
			if (!state->GetPaused()) {
				state->Update(_clock.restart());
			}
		}

		for (const State* state : _removeQueue) {
			for (auto it = _states.begin(); it != _states.end(); it++) {
				if (it->get() == state) {
					_states.erase(it);
					break;
				}
			}
		}
		_removeQueue.clear();
	}

	void StateMachine::DrawStates(const std::shared_ptr<sf::RenderWindow>& window) {
		for (std::shared_ptr<State> state : _states) {
			if (state->GetVisible()) {
				state->Draw(window);
			}
		}
	}

	void StateMachine::ClearAll() {
		_states.clear();
		_removeQueue.clear();
	}
}