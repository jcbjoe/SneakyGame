#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Mesh.h"
#include "Model.h"
#include "FPSCamera.h"


class Player
{
public:

	Player() {
	}
	~Player() {
		Release();
	}
	void Update(float dTime);
	void Render(float dTime);
	void Initialise();
	void Release();
private:
	FPSCamera mCamera;
};

#endif