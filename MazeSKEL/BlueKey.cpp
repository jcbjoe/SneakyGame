#include "BlueKey.h"

BlueKey::BlueKey(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	GetModel().Initialise(*GetMeshManager()->GetMesh("Key"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(0, 0, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Key.dds", true, gd3dDevice);
	mat.texture = "Key.dds";
	GetModel().SetOverrideMat(&mat);
}

void BlueKey::Update(float dTime)
{
	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(0, 0, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Key.dds", true, gd3dDevice);
	mat.texture = "Key.dds";
	mat.texTrsfm.translate = Vector2(i, 0);
	GetModel().SetOverrideMat(&mat);
	i += dTime * 0.5;

	//GetRotation() = GetRotation() + Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), GetRotationAngle() += dTime * 0.5);
	if (getMove()) {
		incrementRotation(dTime * 8, 0, 0);
		y += dTime;
		GetModel().GetPosition() = GetPosition() + Vector3(0, y, 0);
		if (y > 1)
			GetGameObjectManager()->deleteGameObjectByIndex(getIndex());
	}
	else {
		incrementRotation(dTime * 2, 0, 0);
		x += dTime;
		GetModel().GetPosition() = GetPosition() + Vector3(0, sin(x) / 10, 0);
	}
}