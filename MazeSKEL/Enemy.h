#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <vector> 

#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 
#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Enemy : public GameObject
{
public:

	Enemy(string name, Vector3 position, Quaternion rotation, Vector3 scale);

	void setWaypoints(vector<Vector3> wayPointList);
	void Update(float dTime) override;

private:
	vector<Vector3> wayPointsList;
	int waypointNumber;
};

#endif

