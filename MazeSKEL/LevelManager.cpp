#include "LevelManager.h"

#include "level1.h"
#include "level2.h"
#include "GameObjectManager.h"
#include "Skybox.h"
#include "Floor.h"


LevelManager::LevelManager()
{

}

void LevelManager::initialise() {
	Level1* level1 = new Level1("Level1");
	Level2* level2 = new Level2("Level2");

	levels.push_back(level1);
	levels.push_back(level2);

	currentLevelNumber = 0;

	Skybox* skybox = new Skybox("Skybox", Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1, 1, 1));
	GetGameObjectManager()->addGameObject(skybox);

	Floor* floor = new Floor("Floor", Vector3(4.5f, 0.0f, 4.5f), Vector3(0, 0, 0), Vector3(5, 1, 5));
	GetGameObjectManager()->addGameObject(floor);
}

void LevelManager::Release() {
	for (Level* lev : levels) {
		delete lev;
	}
	levels.clear();
}

void LevelManager::loadLevel(string levelname) {
	int count = 0;
	bool found = false;
	for (Level* level : levels) {
		if (level->getLevelName() == levelname) { 
			found = true; break; 
		} else {
			count++;
		}
	}
	if (found) {
		loadLevel(count);
	} else {
		if (!levels.empty())
			loadLevel(0);
	}
}

void LevelManager::loadLevel(int levelNum) {
	levels.at(currentLevelNumber)->Release();
	GetGameObjectManager()->deleteAllObjects();
	currentLevelNumber = levelNum;
	levels.at(currentLevelNumber)->reloadLevel();
}