#include "ReturnBox.h"

ReturnBox::ReturnBox(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{

	//Set up what the box looks like
	GetModel().Initialise(*GetMeshManager()->GetMesh("wall"));

	GetModel().GetScale() = GetScale();
	GetModel().GetPosition() = GetPosition();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Metal.dds", true, gd3dDevice);
	mat.texture = "Metal.dds";

	GetModel().SetOverrideMat(&mat);

	coinsStored = 0;
	coinsRequired = 3;
}

void ReturnBox::Update(float dTime)
{
}
