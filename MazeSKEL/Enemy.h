#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "D3D.h"
#include "Model.h"
#include <vector>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Enemy
{
public:

	Enemy(Vector3, Model&);
	void setWaypoints(vector<Vector3> wayPointList);
	void enemyTick(float);

private:
	Vector3 Pos;
	vector<Vector3> wayPointsList;

	Model& model_;

	int waypointNumber = 0;
};

#endif

