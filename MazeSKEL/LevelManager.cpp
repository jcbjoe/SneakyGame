#include "LevelManager.h"

#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "GameObjectManager.h"
#include "Skybox.h"


LevelManager::LevelManager()
{

}

void LevelManager::initialise() {
	Level1* level1 = new Level1("Level1", 8.0f);
	Level2* level2 = new Level2("Level2", 60.0f);
	Level3* level3 = new Level3("Level3", 60.0f);
	Level4* level4 = new Level4("Level4", 60.0f);
	Level5* level5 = new Level5("Level5", 60.0f);
	Level6* level6 = new Level6("Level6", 120.0f);

	levels.push_back(level1);
	levels.push_back(level2);
	levels.push_back(level3);
	levels.push_back(level4);
	levels.push_back(level5);
	levels.push_back(level6);

	maxLevels = levels.size()-1;

	currentLevelNumber = 0;

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