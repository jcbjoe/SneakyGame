#include "ReturnBox.h"

ReturnBox::ReturnBox(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{

	//Set up what the box looks like
	GetModel().Initialise(*GetMeshManager()->GetMesh("Chest"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 0), Vector4(0.4, 0.4, 0.4, 0), Vector4(0.1, 0.1, 0.1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("chest.dds", true, gd3dDevice);
	mat.texture = "chest.dds";

	GetModel().SetOverrideMat(&mat);

	coinsStored = 0;
	coinsRequired = 3;
}

void ReturnBox::Update(float dTime)
{
}
