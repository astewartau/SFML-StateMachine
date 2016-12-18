#pragma once
#include "State.hpp"

// Forward declaration
class State;

///<summary>Represents a StateMachine which manages and executes game states</summary>
class StateMachine {
public:
	///<summary>Constructs a new StateMachine</summary>
	StateMachine();

	///<summary>Constructs a new StateMachine with an initial state</summary>
	///<param name="initialState">The StateMachine's initial state</param>
	StateMachine(State* initialState);

	///<summary>Sets the StateMachine's current state to the given state. If another state
	///is active, it will be deleted and replaced with the new state.</summary>
	///<param name="newState">The new state</param>
	void SetState(State* newState);

	///<summary>Creates a new SFML window and runs the StateMachine.
	///Execution repeats until the current state is empty (usually user exit).</summary>
	void Run();

	///<summary>Gets the SFML window associated with the StateMachine</summary>
	///<returns>A pointer to the SFML Window</returns>
	sf::RenderWindow* GetWindow();

private:
	// Constants
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;
	const char* WINDOW_TITLE = "State machine";

	///<summary>Code to run before the game loop executes</summary>
	void PreLoop();

	///<summary>Code to run after the game loop executes</summary>
	void PostLoop();

	///<summary>Handle any input received since the last execution</summary>
	void ProcessInput();

	///<summary>Points to the current state</summary>
	State* _currentState;

	///<summary>An SFML clock that provides the deltaTime between executions</summary>
	sf::Clock _clock;

	///<summary>The SFML RenderWindow associated with the StateMachine</summary>
	sf::RenderWindow _window;
};
