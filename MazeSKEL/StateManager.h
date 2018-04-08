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

	void Release();

private:
	int currentState;

	vector<State*> states;
};

SINGLETON_GET(StateManager);

#endif

