#include "LevelManager.h"


LevelManager::LevelManager()
{
	loadLevel(1);
}

LevelManager::LevelManager(int level)
{
	loadLevel(level);
}

int LevelManager::getObjectAtWorldPos(float x, float y)
{
	x = round(x);
	y = round(y);

	return getObjectAtCoordinate(x, y);;
}

void LevelManager::loadLevel(int level)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (level)
			{
			case 1:
				currentLevelNumber = level;
				currentLevelLayout[i][j] = level1[i][j];
				break;
			case 2:
				currentLevelNumber = level;
				currentLevelLayout[i][j] = level2[i][j];
				break;
			default:
				break;
			}
		}
	}
}
