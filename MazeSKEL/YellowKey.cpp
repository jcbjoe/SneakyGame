#include "YellowKey.h"

YellowKey::YellowKey(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	GetModel().Initialise(*GetMeshManager()->GetMesh("Key"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 0, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Key.dds", true, gd3dDevice);
	mat.texture = "Key.dds";
	GetModel().SetOverrideMat(&mat);
}

void YellowKey::Update(float dTime)
{
	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 0, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Key.dds", true, gd3dDevice);
	mat.texture = "Key.dds";
	mat.texTrsfm.translate = Vector2(textMov, 0);
	GetModel().SetOverrideMat(&mat);
	textMov += dTime * 0.5;

	//GetRotation() = GetRotation() + Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), GetRotationAngle() += dTime * 0.5);
	if (getMove()) {
		incrementRotation(dTime * 8, 0, 0);
		collectMov += dTime;
		GetModel().GetPosition() = GetPosition() + Vector3(0, collectMov, 0);
		if (collectMov > 1)
			GetGameObjectManager()->deleteGameObjectByIndex(getIndex());
	}
	else {
		incrementRotation(dTime * 2, 0, 0);
		idleMov += dTime;
		GetModel().GetPosition() = GetPosition() + Vector3(0, sin(idleMov) / 10, 0);
	}
}