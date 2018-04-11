#include "WallHalf.h"

WallHalf::WallHalf(string name, Vector3 position, Vector3 rotation, Vector3 scale)
	:
	GameObject(name, position, rotation, scale)
{
	GetModel().Initialise(*GetMeshManager()->GetMesh("door"));

	GameObject::setInitialPos();

	MaterialExt mat = GetModel().GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(0.8, 1, 0.8, 0), Vector4(0.8f, 0.8f, 0.8f, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("WallStone.dds", true, gd3dDevice);
	mat.texture = "WallStone.dds";

	GetModel().SetOverrideMat(&mat);
}

void WallHalf::Update(float dTime)
{

}