#include "StateMachine.hpp"
#include <algorithm>

namespace sm {
	StateMachine::StateMachine(std::shared_ptr<State> initialState) {
		AddState(initialState);
	}

	void StateMachine::AddState(std::shared_ptr<State> state) {
		// Exception if the state is already managed
		for (auto it = _states.begin(); it != _states.end(); it++) {
			if (it->get() == state.get()) {
				throw StateMachineException("Attempted to add a new state to the state machine, "
					"but the state already exists!");
				return;
			}
		}

		_states.push_back(state);
	}

	void StateMachine::QueueRemoveState(const State* state) {
		if (_removeQueue.find(state) == _removeQueue.end()) {
			_removeQueue.insert(state);
		} else {
			throw StateMachineException("Attempted to queue up a state to remove from the "
				"state machine, but it's already queued!");
		}
	}

	void StateMachine::UpdateStates() {
		// Get time since last update
		sf::Time elapsedTime = _clock.restart();

		// Update states according to state logic
		for (std::shared_ptr<State> state : _states) {
			if (!state->GetPaused()) {
				state->Update(elapsedTime);
			}
		}

		// Process any state removals that have been queued
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