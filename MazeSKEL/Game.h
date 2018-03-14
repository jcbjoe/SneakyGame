#pragma once
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <future>

#include "Mesh.h"
#include "Model.h"
#include "SpriteFont.h"
#include "FPSCamera.h"
#include "Player.h"
#include "Wall.h"
#include "Loot.h"
#include "Floor.h"
#include "UserInterfaceManager.h"
#include "GeometryBuilder.h"
#include "FX.h"
#include "Input.h"
#include "WindowUtils.h"
#include "D3D.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <thread>


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

	Model mSkybox;

	bool isCrouched = false;

private:
	Game& operator=(const Game&) = delete;
	Game(const Game& m) = delete;

	float gAngle = 0;
	FPSCamera mCamera;
	std::vector<Model> mOpaques;

	Wall gWall;
	Player gPlayer;
	Loot gLoot;
	Floor gFloor;

	//Message Handling
	DirectX::SpriteBatch *mpSpriteBatch = nullptr;
	DirectX::SpriteFont *mpFont = nullptr, *mpFont2 = nullptr;
	
};

#endif

