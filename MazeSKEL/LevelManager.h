#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "D3D.h"
#include "D3DUtil.h"
#include "SimpleMath.h"
#include "Singleton.h"
#include <vector>
#include "Level.h"

using namespace std;

class LevelManager : public Singleton<LevelManager>
{
public:

	LevelManager();

	Level* getCurrentLevel() { return levels.at(currentLevelNumber); }
	
	void loadLevel(int levelNum) { currentLevelNumber = levelNum; }

	void loadLevel(string levelname);

	void initialise();
	int getObjectAtWorldPos(float x, float y);

	void Release();

private:
	int currentLevelNumber;

	vector<Level*> levels;
};

SINGLETON_GET(LevelManager);

#endif

