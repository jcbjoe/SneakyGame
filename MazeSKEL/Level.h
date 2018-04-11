#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "D3D.h"
#include "D3DUtil.h"

class Player;

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Level
{
public:
	Level(string levelName);

	void setLevelMap(int[20][20]);

	int getObjectAtCoordinate(int x, int y) { return levelMap[x][y]; }

	string getLevelName();

	void reloadLevel();

	virtual void Release();

	int getObjectAtWorldPos(float x, float y);

	int getMaxCoins() const { return maxCoins; }

	void addWaypointLocation(Vector3 loc);

private:

	string levelName;

	int levelMap[20][20];
	int maxCoins;

	vector<Vector3> waypointLocations;
};


#endif