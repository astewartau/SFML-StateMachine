#pragma once
#include <memory>

// Forward declarations for SFML classes
namespace sf { class Time; class RenderWindow; }

namespace sm {
	///<summary>Enumeration of State statuses</summary>
	enum Status {
		ACTIVATED,   ///<summary>An active state that is updated and drawn to the window</summary>
		DEACTIVATED, ///<summary>An inactive state that is neither updated nor drawn</summary>
		PAUSED		 ///<summary>A semi-active state that is drawn to the window but not updated</summary>
	};

	///<summary>Represents an executable game state</summary>
	class State {
	public:
		///<summary>Constructs a new state</summary>
		///<param name="status">The intial status of the new state</param>
		State(Status status = Status::ACTIVATED) : _status(status) {}

		///<summary>Handles state-specific logic</summary>
		///<param name="deltaTime">Time since the previous execution</param>
		virtual void Update(sf::Time deltaTime) = 0;

		///<summary>Handles state-specific rendering</summary>
		///<param name="window">A pointer to the window to render the state to</param>
		virtual void Draw(const std::shared_ptr<sf::RenderWindow>& window) = 0;

		///<summary>Sets the status of the state</summary>
		///<param name="status">The status to set the state to</param>
		void SetStatus(Status status) { _status = status; }

		///<summary>Gets the status of the state</summary>
		///<returns>The current status of the state</returns>
		Status GetStatus() { return _status; }
	private:
		///<summary>The current status of the state</summary>
		Status _status;
	};
}