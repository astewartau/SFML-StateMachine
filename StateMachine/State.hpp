#pragma once
#include <SFML\Graphics.hpp>
#include "StateMachine.hpp"

// Forward declaration
class StateMachine;

///<summary>Represents an executable game state</summary>
class State {
public:
	///<summary>Constructs a new state</summary>
	State();

	///<summary>Initialises the state for execution.</summary>
	///<param name="stateMachine">The StateMachine associated with this state.</param>
	bool Init(StateMachine* stateMachine);

	///<summary>Executes and draws the state to the window. Only runs if the state
	///has been initialised.</summary>
	///<param name="deltaTime">Time since the previous execution</param>
	///<returns>A pointer to the next state</returns>
	State* Execute(int deltaTime);

private:
	///<summary>State-specific initialisation, run at the end of Init().</summary>
	virtual void InitState() = 0;

	///<summary>Virtual function to implement state logic</summary>
	///<param name="deltaTime">Time since the previous execution</param>
	virtual void Update(int deltaTime) = 0;

	///<summary>Clears the renderer and then Draws the state to the screen</summary>
	void DrawAll();

	///<summary>Virtual function to draw the state to the screen</summary>
	virtual void Draw() = 0;

protected:
	///<summary>Points to the state to be executed next</summary>
	State* _nextState;

	///<summary>Points to the StateMachine running this state</summary>
	StateMachine* _stateMachine;

	///<summary>Points to the StateMachine's window</summary>
	sf::RenderWindow* _window;
};

