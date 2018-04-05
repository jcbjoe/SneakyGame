#include "Levels.h"

Levels::Levels()
{
	loadLevel(1);
}

Levels::Levels(int level)
{
	loadLevel(level);
}

void Levels::loadLevel(int level)
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
