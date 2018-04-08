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
#include "Enemy.h"
#include "WindowUtils.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Key.h"
#include "Door.h"

#include "GameObjectManager.h"
#include "LevelManager.h"
#include "StateManager.h"

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

	//Message handling
	LRESULT WindowsMssgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool isCrouched = false;
	void Release();

private:
	Game& operator=(const Game&) = delete;
	Game(const Game& m) = delete;

	float gAngle = 0;
	Player gPlayer;
	
	

	

	int width;
	int height;

	//Enemy mEnemy;
	vector<Enemy> enemysVector;
	vector<Vector3> waypointsVector;


};

#endif

