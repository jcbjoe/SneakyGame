#include "Enemy.h"

Enemy::Enemy(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	waypointNumber = 1;

	GetModel().Initialise(*GetMeshManager()->GetMesh("cube"));

	GetModel().GetScale() = GetScale();
	GetModel().GetPosition() = GetPosition();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Enemy.dds", true, gd3dDevice);
	mat.texture = "Enemy.dds";
	mat.texTrsfm.scale = Vector2(1, 1);

	GetModel().SetOverrideMat(&mat);
}

void Enemy::Update(float dTime) {

	GameObject* waypoint = GetGameObjectManager()->getFirstObjectByName("Waypoint" + to_string(waypointNumber));

	float distance = Vector3().Distance(GetModel().GetPosition(), waypoint->GetPosition());

	Vector3 pos = Vector3::Lerp(GetModel().GetPosition(), waypoint->GetPosition(), (1*dTime) / distance);

	SetPosition(pos);

	
	if (distance < 0.1) {
		if(waypointNumber == 8) 
			waypointNumber = 1;
		else
			waypointNumber++;
	
	}
	//GetUserInterfaceManager()->printDebugText(to_string(test));
}
