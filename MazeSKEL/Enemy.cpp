#include "Enemy.h"
#include "StateManager.h"
#include "GameState.h"

Enemy::Enemy(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	waypointNumber = 1;

	GetModel().Initialise(*GetMeshManager()->GetMesh("cube"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Enemy.dds", true, gd3dDevice);
	mat.texture = "Enemy.dds";
	mat.texTrsfm.scale = Vector2(1, 1);

	GetModel().SetOverrideMat(&mat);
}

void Enemy::Update(float dTime) {

	Vector3 playerPos = ((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCameraPosition();

	bool canSeeBool = true;

	vector<Vector2> inbetween = canSee(round(playerPos.x), round(playerPos.z), round(GetModel().GetPosition().x), round(GetModel().GetPosition().z));

	for (Vector2 coords : inbetween) {
		int objType = GetLevelManager()->getCurrentLevel()->getObjectAtWorldPos(coords.x, coords.y);
		if (objType == 1) {
			canSeeBool = false;
			break;
		}
	}

	float distance = Vector3().Distance(GetModel().GetPosition(), playerPos);

	if (canSeeBool) {
		if (((GameState*)GetStateManager()->getCurrentState())->getPlayer()->getCrouchStatus()) {
			if (distance > 1.5) {
				canSeeBool = false;
			}
		} else {
			if (distance > 3) {
				canSeeBool = false;
			}
		}
	}


	if (canSeeBool) {

		Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), playerPos, (1 * dTime) / distance);

		SetPosition(pos);


	} else {


		GameObject* waypoint = GetGameObjectManager()->getFirstObjectByName("Waypoint" + to_string(waypointNumber));

		float distance = Vector3().Distance(GetModel().GetPosition(), waypoint->GetPosition());

		Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), waypoint->GetPosition(), (1 * dTime) / distance);

		SetPosition(pos);


		if (distance < 0.1) {
			if (waypointNumber == 8)
				waypointNumber = 1;
			else
				waypointNumber++;

		}
	}
}

vector<Vector2> Enemy::canSee(int x0, int y0, int x1, int y1)
{
	vector<Vector2> blocks;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x = x0;
	int y = y0;
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{

		blocks.push_back({ (float)x,(float)y });

		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}

	return blocks;
}
