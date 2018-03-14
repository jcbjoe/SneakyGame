#ifndef GAME_H
#define GAME_H

#include <vector>
#include <future>

#include "SpriteFont.h"
#include "Player.h"
#include "Wall.h"
#include "Loot.h"
#include "Floor.h"
#include "Skybox.h"
#include "UserInterfaceManager.h"
#include "GeometryBuilder.h"
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

private:
	Game& operator=(const Game&) = delete;
	Game(const Game& m) = delete;

	float gAngle = 0;
	std::vector<Model> mOpaques;

	Wall gWall;
	Player gPlayer;
	Loot gLoot;
	Floor gFloor;
	Skybox gSkybox;

	//Message Handling
	DirectX::SpriteBatch *mpSpriteBatch = nullptr;
	DirectX::SpriteFont *mpFont = nullptr, *mpFont2 = nullptr;
	
};

#endif

