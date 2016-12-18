#include "StateMachine/StateMachine.hpp"
#include "DemoState.hpp"

int main() {
	StateMachine stateMachine;
	stateMachine.SetState(new DemoState());
	stateMachine.Run();

	printf("Press ENTER to exit");
	std::getchar();
	return 0;
}
