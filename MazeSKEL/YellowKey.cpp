#include "YellowKey.h"

YellowKey::YellowKey(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	GetModel().Initialise(*GetMeshManager()->GetMesh("loot"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 0, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Key.dds", true, gd3dDevice);
	mat.texture = "Key.dds";
	GetModel().SetOverrideMat(&mat);
}

void YellowKey::Update(float dTime)
{
	//GetRotation() = GetRotation() + Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), GetRotationAngle() += dTime * 0.5);
	if (getMove()) {
		incrementYRotation(dTime * 8);
		y += dTime;
		GetModel().GetPosition() = GetPosition() + Vector3(0, y, 0);
		if (y > 1)
			GetGameObjectManager()->deleteGameObjectByIndex(getIndex());
	}
	else {
		incrementYRotation(dTime * 2);
		x += dTime;
		GetModel().GetPosition() = GetPosition() + Vector3(0, sin(x) / 10, 0);
	}
}