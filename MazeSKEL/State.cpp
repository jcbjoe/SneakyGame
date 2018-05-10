#include "State.h"

//Base class for all states

//Constructor
State::State(string name)
	:
	stateName(name)
{

}

void State::Init() {

}

void State::Update(float dTime)
{

}

void State::Render(float dTime)
{

}

void State::ReleaseFromLevel() {

}

void State::Destruct() {

}