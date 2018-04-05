#include "LevelManager.h"



#include "level1.h"

LevelManager::LevelManager()
{
	Level1 level1("Level1");

	levels.push_back(level1);

	loadLevel(0);
}
