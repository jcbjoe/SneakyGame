#include "Loot.h" 

void Loot::Initialise()
{
	mLoot.Initialise(BuildLoot(*GetMeshManager(), 10, 10));
	mLoot.GetScale() = Vector3(0.1f, 0.1f, 0.1f);
	mLoot.GetPosition() = Vector3(0, -0.5f, 1);
	MaterialExt mat = mLoot.GetMesh().GetSubMesh(0).material;
	mat.gfxData.Set(Vector4(0.5, 0.5, 0.5, 1), Vector4(1, 1, 1, 0), Vector4(1, 1, 1, 1));
	mat.pTextureRV = FX::GetMyFX()->mCache.LoadTexture("Metal.dds", true, gd3dDevice);
	mat.texture = "Metal.dds";
	mLoot.SetOverrideMat(&mat);
}

void Loot::Release()
{
}

void Loot::Update(float dTime)
{

}

void Loot::Render(float dTime)
{
	//render all the solid models first in no particular order 
	for (Model*p : mOpaques)
		FX::GetMyFX()->Render(*p, gd3dImmediateContext);
}

Model Loot::getModel()
{
	return mLoot;
}

void Loot::setPosition(const float& x, const float& y, const float& z)
{
	mLoot.GetPosition() = Vector3(x, y, z);
}

void Loot::setRotation(const float& angleX, const float& angleY, const float& angleZ)
{
	mLoot.GetRotation() = Vector3(angleX, angleY, angleZ);
}