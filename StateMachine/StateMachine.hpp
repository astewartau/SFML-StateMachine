#pragma once
#include <queue>
#include <memory>
#include <SFML\System\Clock.hpp>
#include "State.hpp"

// Forward declaration
namespace sf { class RenderWindow; }

namespace sm {
	///<summary>Represents a StateMachine which manages and executes game states</summary>
	class StateMachine {
	public:
		///<summary>Constructs a new StateMachine</summary>
		StateMachine() {};

		///<summary>Constructs a new StateMachine with the given initial state</summary>
		///<param name="initialState">A pointer to the initial state for the StateMachine</param>
		StateMachine(std::shared_ptr<State> initialState);

		///<summary>Adds the given state to the state machine for processing on execution</summary>
		///<param name="state">A pointer to the state to add to the state machine</param>
		void AddState(std::shared_ptr<State> state);

		///<summary>Sets the given state to the given status at the end of the next 
		///execution cycle.</summary>
		///<param name="state">A pointer to the state to set the status of</param>
		///<param name="status">The new status of the state</param>
		void QueueStateChange(std::shared_ptr<State> state, Status status);

		///<summary>Updates active states according to state logic. Additionally, 
		///makes status changes to live states and adds and removes states as necessary.</summary>
		void UpdateStates();

		///<summary>Updates active and paused states</summary>
		///<param name="window">A pointer to the window to draw active and paused states to</param>
		void DrawStates(const std::shared_ptr<sf::RenderWindow>& window);
	private:
		///<summary>Processes queued state changes from the action queue</summary>
		void ProcessStateChanges();

		///<summary>A vector of states and their associated status</summary>
		std::vector<std::shared_ptr<State>> _states;

		///<summary>A queue of actions to occur at the end of an execution</summary>
		std::queue<std::pair<std::shared_ptr<State>, Status>> _actionQueue;

		///<summary>An SFML clock that provides the deltaTime between executions</summary>
		sf::Clock _clock;
	};
}