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

	~LevelManager() {
		Release();
	}

	Level* getCurrentLevel() { return levels.at(currentLevelNumber); }
	
	void loadLevel(int levelNum);

	void loadLevel(string levelname);

	void initialise();

	void Release();

	int getCurrentLevelNumber() const { return currentLevelNumber; }

	int getMaxLevels() const { return maxLevels; }

private:
	int currentLevelNumber;
	int maxLevels;

	vector<Level*> levels;
};

SINGLETON_GET(LevelManager);

#endif

