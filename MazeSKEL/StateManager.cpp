#include "StateManager.h"
#include "GameState.h"

StateManager::StateManager()
{
	GameState* gameState = new GameState();

	states.push_back(gameState);

	currentState = 0;
}

State* StateManager::getCurrentState() {
	return states.at(currentState);
}

void StateManager::Release() {

}
