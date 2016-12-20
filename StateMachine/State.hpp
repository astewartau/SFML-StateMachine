#pragma once
#include <SFML\Graphics.hpp>
#include "StateMachine.hpp"

namespace sm {
	// Forward declaration
	class StateMachine;

	///<summary>Enumeration of State statuses</summary>
	enum Status {
		ACTIVATED,   // An active state that is updated and drawn to the window
		DEACTIVATED, // An inactive state that is neither updated nor drawn
		PAUSED		 // A semi-active state that is drawn to the window but not updated
	};

	///<summary>Represents an executable game state</summary>
	class State {
	public:
		///<summary>Constructs a new state</summary>
		State::State(Status status = Status::ACTIVATED) : _nextState(this), _status(status) {}

		///<summary>State-specific logic</summary>
		///<param name="deltaTime">Time since the previous execution</param>
		virtual void Update(sf::Time deltaTime) = 0;

		///<summary>State-specific rendering</summary>
		virtual void Draw(sf::RenderWindow* window) = 0;

		///<summary>Sets the status of the state</summary>
		void SetStatus(Status status) { _status = status; }

		///<summary>Gets the status of the state</summary>
		Status GetStatus() { return _status; }

	protected:
		///<summary>Points to the state to be executed next</summary>
		State* _nextState;

		///<summary>The current status of the state</summary>
		Status _status;
	};
}