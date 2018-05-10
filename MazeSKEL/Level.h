#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "D3D.h"
#include "D3DUtil.h"
#include "FX.h"

class Player;

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Level
{
public:
	Level(string n, float t);

	const static int levelSize = 20;

	void setLevelMap(int[levelSize][levelSize]);

	int getObjectAtCoordinate(int x, int y);

	string getLevelName();

	float getLevelTimer() { return timer; }

	void reloadLevel();

	virtual void Release();

	int getObjectAtWorldPos(float x, float y);

	int getMaxCoins() const { return maxCoins; }

	void addWaypointLocation(Vector3 loc);

	int getHowManyWaypoints();

private:

	string levelName;
	float timer;
	 
	int levelMap[levelSize][levelSize]; 
	int maxCoins;
	bool windowWall = false;
	vector<Vector3> waypointLocations;

};


#endif