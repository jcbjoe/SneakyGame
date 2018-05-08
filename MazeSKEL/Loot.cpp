#include "Loot.h" 

Loot::Loot(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale) {

	GetModel().Initialise(*GetMeshManager()->GetMesh("Coin"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.8, 0.8, 0.8, 1), Vector4(0.6, 0.6, 0.6, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("CoinBase.dds", true, gd3dDevice);
	mat.texture = "CoinBase.dds";
	GetModel().SetOverrideMat(&mat);
}

void Loot::Update(float dTime)
{
	//GetRotation() = GetRotation() + Quaternion::CreateFromAxisAngle(Vector3(0, 1, 0), GetRotationAngle() += dTime * 0.5);
	if (getMove()) {
		//Change Lighting
			MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
			mat.gfxData.Set(Vector4(0.8, 0.8, 0.8, 1), Vector4(y, y, y, 0), Vector4(1, 1, 1, 1));
			mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("CoinBase.dds", true, gd3dDevice);
			mat.texture = "CoinBase.dds";
			GetModel().SetOverrideMat(&mat);
			y += dTime * 1.5;
		//Rotation
			incrementRotation(0, dTime * 10, 0);
		//Scale
			x += dTime * 0.02;
			GetModel().GetScale() = GetScale() - Vector3(x, x, x);
		if (x > 0.02)
			GetGameObjectManager()->deleteGameObjectByIndex(getIndex());
	}
	else {
		incrementRotation(0, dTime * 1.0f, 0);
		z += dTime;
		GetModel().GetPosition() = GetPosition() + Vector3(0, sin(z) / 20, 0);
	}
}