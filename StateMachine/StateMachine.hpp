#pragma once
#include <queue>
#include <memory>
#include <SFML\Graphics.hpp>
#include "State.hpp"

namespace sf { class Clock; class RenderWindow; }

namespace sm {
	///<summary>Represents a StateMachine which manages and executes game states</summary>
	class StateMachine {
	public:
		///<summary>Constructs a new StateMachine</summary>
		StateMachine(const std::shared_ptr<sf::RenderWindow>& window);

		///<summary>Constructs a new StateMachine with the given initial state</summary>
		///<param name="initialState">The initial state for the StateMachine</param>
		StateMachine(const std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<State> initialState);

		///<summary>Executes the StateMachine. The result is a newly constructed frame 
		///rendered to the SFML window based on input processing and state logic.</summary>
		void Execute();

		///<summary>Adds the given state to the state machine for processing on execution</summary>
		///<param name="state">The state to add to the state machine</param>
		void AddState(std::shared_ptr<State> state);

		///<summary>Sets the given state to the given status at the end of the next 
		///execution cycle.</summary>
		///<param name="state">A pointer to the state to set the status of</param>
		///<param name="status">The new status of the state</param>
		void QueueStateChange(std::shared_ptr<State> state, Status status);

		///<summary>Gets the SFML window associated with the StateMachine</summary>
		///<returns>A pointer to the SFML Window</returns>
		std::shared_ptr<sf::RenderWindow> GetWindow();

		///<summary>Returns true if the user has quit</summary>
		///</returns>True if the the user has quit</returns>
		bool GetUserQuit();

	private:

		///<summary>Handle any input received since the last execution</summary>
		void ProcessInput();

		///<summary>Updates active states according to state logic</summary>
		void UpdateStates();

		///<summary>Updates active and paused states</summary>
		void DrawStates();

		///<summary>Processes queued state changes from the action queue</summary>
		void ProcessStateChanges();

		///<summary>A vector of states and their associated status</summary>
		std::vector<std::shared_ptr<State>> _states;

		///<summary>A queue of actions to occur at the end of an execution</summary>
		std::queue<std::pair<std::shared_ptr<State>, Status>> _actionQueue;

		///<summary>An SFML clock that provides the deltaTime between executions</summary>
		sf::Clock _clock;

		///<summary>Points to the SFML RenderWindow associated with the StateMachine</summary>
		std::shared_ptr<sf::RenderWindow> _window;

		///<summary>True if the user has quit</summary>
		bool _userQuit;
	};
}