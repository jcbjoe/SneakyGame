#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "D3D.h"
#include "Model.h"
#include "UserInterfaceManager.h"
#include <vector>

#include "Mesh.h" 
#include "Model.h" 
#include "GeometryBuilder.h" 
#include "FX.h" 
#include "GameObject.h"
#include "GameObjectManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Enemy : public GameObject
{
public:

	Enemy(string name, Vector3 position, Vector3 rotation, Vector3 scale);

	void Update(float dTime) override;

private:
	int waypointNumber;
	vector<Vector2> canSee(int x0, int y0, int x1, int y1);
};

#endif

