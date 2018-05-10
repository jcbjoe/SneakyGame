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
	~StateManager() {
		Release();
	}

	State* getCurrentState();

	void changeState(string stateName);
	void changeState(int stateNumb);

	void Release();

	string getCurrentStateName();

	bool recordPress;

	void Update(float dTime);

	void Render(float dTime);

private:
	int currentState;

	vector<State*> states;
};

SINGLETON_GET(StateManager);

#endif

