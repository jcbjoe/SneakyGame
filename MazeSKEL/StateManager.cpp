#include "StateManager.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "LoadingState.h"
#include "GameOverState.h"
#include "HighscoreState.h"
#include "HelpState.h"

StateManager::StateManager()
{
	MainMenuState* mainMenuState = new MainMenuState();
	GameState* gameState = new GameState();
	LoadingState* loadingState = new LoadingState();
	GameOverState* gameOverState = new GameOverState();
	HighscoreState* highscoreState = new HighscoreState();
	HelpState* helpState = new HelpState();

	states.push_back(mainMenuState);
	states.push_back(gameState);
	states.push_back(loadingState);
	states.push_back(gameOverState);
	states.push_back(highscoreState);
	states.push_back(helpState);
	

	currentState = 0;

	recordPress = false;
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
		recordPress = true;
		getCurrentState()->ReleaseFromLevel();
		currentState = counter;
		getCurrentState()->Init();
	}
}

void StateManager::changeState(int stateNumb) {
	if (stateNumb <=  states.size()) {
		getCurrentState()->ReleaseFromLevel();
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

void StateManager::Update(float dTime) {
	getCurrentState()->Update(dTime);
}

void StateManager::Render(float dTime) {
	getCurrentState()->Render(dTime);
}