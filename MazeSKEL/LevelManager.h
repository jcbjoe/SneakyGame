#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Singleton.h"
#include <vector>
#include "Level.h"

using namespace std;

class LevelManager : public Singleton<LevelManager>
{
public:

	LevelManager();

	int level1[10][10] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 3, 0, 0, 0, 0, 0, 0, 4, 1 },
		{ 1, 6, 5, 1, 0, 1, 0, 6, 0, 1 },
		{ 1, 0, 0, 1, 1, 1, 0, 5, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 1, 0, 0, 3, 0, 0, 0, 1 },
		{ 1, 3, 0, 3, 0, 6, 5, 2, 0, 1 },
		{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	int level2[10][10] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 3, 0, 0, 0, 0, 0, 0, 4, 0 },
		{ 0, 6, 5, 1, 0, 1, 0, 6, 0, 0 },
		{ 0, 2, 0, 1, 1, 1, 0, 5, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
		{ 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 3, 0, 0, 0, 0 },
		{ 0, 3, 0, 3, 0, 6, 5, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 }
	};

	Level getCurrentLevel() { return levels.at(currentLevelNumber); }
	
	void loadLevel(int levelNum) { currentLevelNumber = levelNum; }

private:
	int currentLevelNumber;

	vector<Level> levels;
};

SINGLETON_GET(LevelManager);

#endif

