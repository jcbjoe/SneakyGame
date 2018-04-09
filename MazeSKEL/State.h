#ifndef STATE_H
#define STATE_H

#include <string>
#include <vector>
#include <future>

#include "GameObjectManager.h"
#include "LevelManager.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class State
{
public:
	State(string name);

	virtual void Init();

	virtual void Update(float dTime);

	virtual void Render(float dTime);

	string getStateName() { return stateName; }

private:

	const string stateName;

};


#endif