#include "StateManager.h"
#include "GameState.h"
#include "MainMenuState.h"

StateManager::StateManager()
{
	MainMenuState* mainMenuState = new MainMenuState();
	GameState* gameState = new GameState();

	states.push_back(mainMenuState);
	states.push_back(gameState);
	

	currentState = 0;
}

State* StateManager::getCurrentState() {
	return states.at(currentState);
}

void StateManager::changeState(string stateName) {
	bool found = false;
	int counter = 0;
	for (State* state : states) {
		if (state->getStateName() == stateName) {
			found = true;
			break;
		}
		counter++;
	}

	if (found) {
		currentState = counter;
		getCurrentState()->Init();
	}
}

void StateManager::changeState(int stateNumb) {
	if (stateNumb <=  states.size()) {
		currentState = stateNumb;
		getCurrentState()->Init();
	}
}

void StateManager::Release() {

}
