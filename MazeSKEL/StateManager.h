#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Singleton.h"
#include <vector>
#include "State.h"

using namespace std;

class StateManager : public Singleton<StateManager>
{
public:

	StateManager();

	State* getCurrentState();

	void changeState(string stateName);
	void changeState(int stateNumb);

	void Release();

	string getCurrentStateName();

private:
	int currentState;

	vector<State*> states;
};

SINGLETON_GET(StateManager);

#endif

