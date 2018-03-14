#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <future>

#include "Mesh.h"
#include "Model.h"
#include "SpriteFont.h"
#include "FPSCamera.h"
#include "UserInterfaceManager.h"


class Game
{
public:

	Game() {}
	~Game() {
		Release();
	}
	void Update(float dTime);
	void Render(float dTime);
	void OnResize(int screenWidth, int screenHeight);
	void Initialise();
	void Release();

	//Message handling
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	Model mBox, mWall, mQuad, mSkybox, mLoot;
	

	float maxX, maxY;

	bool isCrouched = false;

private:
	Game& operator=(const Game&) = delete;
	Game(const Game& m) = delete;

	

	float gAngle = 0;
	FPSCamera mCamera;
	std::vector<Model> mOpaques;

	//Message Handling
	void LoadDisplay(float dTime);
	
};

#endif

