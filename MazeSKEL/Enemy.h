#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "D3D.h"
#include <vector>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Enemy
{
public:

	Enemy(Vector3 position);
	void setWaypoints(vector<Vector3> wayPointList);


private:
	Vector3 Pos;
	vector<Vector3> wayPointsList;
};

#endif

