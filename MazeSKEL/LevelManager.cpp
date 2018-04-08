#include "LevelManager.h"



#include "level1.h"
#include "level2.h"

LevelManager::LevelManager()
{
	Level1 level1("Level1");
	Level2 level2("Level2");

	levels.push_back(level1);
	levels.push_back(level2);

	loadLevel(0);
}

void LevelManager::loadLevel(string levelname) {
	int count = 0;
	bool found = false;
	for (Level level : levels) {
		if (level.getLevelName() == levelname) { 
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