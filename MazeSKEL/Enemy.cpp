#include "Enemy.h"
#include "UserInterfaceManager.h"


Enemy::Enemy(string name, Vector3 position, Quaternion rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	waypointNumber = 1;

	GetModel().Initialise(*GetMeshManager()->GetMesh("wall"));

	GetModel().GetScale() = GetScale();
	GetModel().GetPosition() = GetPosition();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Enemy.dds", true, gd3dDevice);
	mat.texture = "Enemy.dds";
	mat.texTrsfm.scale = Vector2(1, 1);

	GetModel().SetOverrideMat(&mat);
}

void Enemy::setWaypoints(vector<Vector3> wayPoints) {
	wayPointsList = wayPoints;
}

void Enemy::Update(float dTime) {
	//model_->GetPosition(Vector3(model_))
	Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), wayPointsList.at(waypointNumber), 1*dTime);
	//GetUserInterfaceManager()->printDebugText(to_string(pos.x) + " : " + to_string(pos.z));
	GetModel().GetPosition() = pos;

	float test = Vector3().Distance(GetModel().GetPosition(),wayPointsList.at(waypointNumber));
	if (test < 0.1) {
		waypointNumber++;
	
	}
	GetUserInterfaceManager()->printDebugText(to_string(test));
}
