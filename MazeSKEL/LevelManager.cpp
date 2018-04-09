#include "LevelManager.h"



#include "level1.h"
#include "level2.h"

LevelManager::LevelManager()
{
	Level1* level1 = new Level1("Level1");
	Level2* level2 = new Level2("Level2");

	levels.push_back(level1);
	levels.push_back(level2);

	loadLevel(0);
}

void LevelManager::loadLevel(string levelname) {
	levels.at(currentLevelNumber)->Release();
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