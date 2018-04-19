#include "StateManager.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "LoadingState.h"
#include "GameOverState.h"

StateManager::StateManager()
{
	MainMenuState* mainMenuState = new MainMenuState();
	GameState* gameState = new GameState();
	LoadingState* loadingState = new LoadingState();
	GameOverState* gameOverState = new GameOverState();

	states.push_back(mainMenuState);
	states.push_back(gameState);
	states.push_back(loadingState);
	states.push_back(gameOverState);
	

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
		getCurrentState()->Release();
		currentState = counter;
		getCurrentState()->Init();
	}
}

void StateManager::changeState(int stateNumb) {
	if (stateNumb <=  states.size()) {
		getCurrentState()->Release();
		currentState = stateNumb;
		getCurrentState()->Init();
	}
}

void StateManager::Release() {
	for (State* stat : states) {
		delete stat;
	}
	states.clear();
}

string StateManager::getCurrentStateName() {
	return getCurrentState()->getStateName();
}