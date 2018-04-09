#ifndef LEVELS_H
#define LEVELS_H

#include "D3D.h"
#include "D3DUtil.h"
#include "SimpleMath.h"
#include "Singleton.h"

class LevelManager : public Singleton<LevelManager>
{
public:

	LevelManager();
	LevelManager(int level);

	int level1[10][10] =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 3, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 3, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 3, 2, 0, 0, 7, 0, 1 },
		{ 1, 0, 0, 3, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 3, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
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

	void loadLevel(int level);
	int getCurrentLevel() { return currentLevelNumber; }
	int getObjectAtCoordinate(int x, int y) { return currentLevelLayout[x][y]; }
	int getObjectAtWorldPos(float x, float y);

private:
	int currentLevelLayout[10][10];
	int currentLevelNumber;
};

SINGLETON_GET(LevelManager);

#endif

